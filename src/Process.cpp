//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Process.h"
#include <thread>   // std::this_thread::sleep_for
#include <iomanip>  // std::setprecision
#include <sstream>  // sstreamstring
#include <memory>
#include <exception>

using namespace std::chrono_literals;

Process::Process(int width, int height, double fruitEmptiness,
                 int totalPlayers, std::string* playerNames)
    : totalPlayers(totalPlayers), isGamingContinue(true)
{
    field       = std::make_shared  <Field>   (width, height);
    fruit       = std::make_unique  <Fruit>   (fruitEmptiness, field);
    graphic     = std::make_unique  <Graphic> (field);
    players     = std::make_unique<std::unique_ptr<Player> []> (totalPlayers+1);
    snakes      = std::make_unique<std::shared_ptr<Snake>  []> (totalPlayers+1);

    // spawn player's id and names
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        players[playerId] = std::make_unique<Player>(playerId, playerNames[playerId]);
        snakes[playerId] = std::make_unique<Snake>(nullptr, totalPlayers, playerId, field); // snakes[playerId] = new Snake(playerId, *field);
    }

    this->mainLoop();
}

void Process::mainLoop()
{
    int eattenFruitElement = 0;
    int playerGameOverReason[4] = {0,0,0,0};
    int playerPoints[4] = {0,0,0,0};
    std::string playerStats[4] = {"","","",""};

    this->start_time =
        std::chrono::high_resolution_clock::now();

    while (true)
    {
        int playerInput[4] = {-1,-1,-1,-1};
        int keyboardCode = keyboard.getMyKeyboardCode();

        // split keybord input to players
        if (keyboardCode >= 10 && keyboardCode <=13)
            playerInput[0] = keyboardCode - 10;
        else if (keyboardCode >= 20 && keyboardCode <=23)
            playerInput[1] = keyboardCode - 20;
        else if (keyboardCode >= 30 && keyboardCode <=33)
            playerInput[2] = keyboardCode - 30;
        else if (keyboardCode >= 40 && keyboardCode <=43)
            playerInput[3] = keyboardCode - 40;

        // clear
        graphic->clearVideoBuffer();

        // wall
        graphic->addWallsToVideoBuffer();

        // fruit
        graphic->addFruitToVideoBuffer(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        // go through sneakes
        for (int snInst = 0; snInst < this->totalPlayers; snInst ++)
        {

            if (!snakes[snInst]->isSnakeDie())
                snakes[snInst]->setSnakeDirectionAndShift(playerInput[snInst]);

            graphic->addSnakeToVideoBuffer(snInst,
                                           snakes[snInst]->getSnakeX(),
                                           snakes[snInst]->getSnakeY(),
                                           snakes[snInst]->getSnakeLength(),
                                           snakes[snInst]->isSnakeDie());


            if ( (eattenFruitElement = snakes[snInst]->getElementOfEattenFruit(
                                           fruit->getFruitX(),
                                           fruit->getFruitY(),
                                           fruit->getTotalFruit())) > 0)
            {
                snakes[snInst]->growUpSnake();
                fruit->refreshFruit(eattenFruitElement-1);
                Beep(5300, 10);
            }


            // conflict check
            if (!snakes[snInst]->isSnakeDie())
            {
                playerGameOverReason[snInst] = snakes[snInst]->isSnakeInConflict();

                for (int tail = 0; tail < snakes[snInst]->getSnakeLength(); tail++)
                {

//                    if ( (getSnakeX()[0] == snakes[snInst]->backupCoosX[tail] &&
//                            snakeHeadY == snakes[snInst]->backupCoosY[tail]) )
//                        playerGameOverReason = 3;

                }

                if ( playerGameOverReason[snInst] == 1
                        || playerGameOverReason[snInst] == 2
                        || playerGameOverReason[snInst] == 3)
                {
                    snakes[snInst]->setSnakeDie();
                    // Graphic->coutGOver(gameOverReason);
                    // break;

                }
            }

            std::string dieBye;
            if (snakes[snInst]->getSnakeDieReason() == 1 )
                dieBye = "wall";
            else if (snakes[snInst]->getSnakeDieReason() == 2 )
                dieBye = "self";
            else if (snakes[snInst]->getSnakeDieReason() == 3)
                dieBye = "another Snake";

            playerPoints[snInst] = snakes[snInst]->getSnakeLength() * SCORE_MULTIPLIER;
            playerStats[snInst] = "Player " + players[snInst]->getPlayerName() + " Points: " + std::to_string(playerPoints[snInst]) +
                             (snakes[snInst]->isSnakeDie() ? " Dead by " + dieBye : "");
        }

        graphic->redrawVideoBuffer();

        // print player stats
        for (int i = 0; i < 4; i++)
            graphic->coutVCentered(playerStats[i]);

        // print elapsed time
        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time=
            (this->end_time - this->start_time) / 1000;

        msg = "Duration: "
              + std::to_string((int)this->elapsed_time.count()) + "s";
        graphic->coutVCentered(msg);
        graphic->coutVCentered("(H)elp | (R)estart | e(X)it");

        // exit game
        if (keyboardCode == 4)
        {
            this->isGamingContinue = false;
            break;
        }

        // help game
        if (keyboardCode == 5)
            graphic->coutHelp();

        // restart game
        if (keyboardCode == 6)
            break;

        // retarder
        std::this_thread::sleep_for(150ms);
    }
}

bool Process::isGaming() const
{
    return this->isGamingContinue;
}
