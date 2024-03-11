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
        snakes[playerId] = std::make_unique<Snake>(playerId, field->getFieldWidth()/2, field->getFieldHeight()/2); // snakes[playerId] = new Snake(playerId, *field);
    }

    this->mainLoop();
}

void Process::mainLoop()
{
    int eattenFruitElement = 0;
    int snakeDiedReason[4] = {0,0,0,0};
    int playerPoints[4] = {0,0,0,0};
    bool isAllDead = false;
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

        // go through snakes
        for (int currSnake = 0; currSnake < this->totalPlayers; currSnake ++)
        {
            snakes[currSnake]->setMyDirectionAndShift(playerInput[currSnake]);

            graphic->addSnakeToVideoBuffer(currSnake,
                                           snakes[currSnake]->getSnakeX(),
                                           snakes[currSnake]->getSnakeY(),
                                           snakes[currSnake]->getSnakeLength(),
                                           snakes[currSnake]->amIDead());


            if ( (eattenFruitElement = snakes[currSnake]->getElementOfEattenFruit(
                                           fruit->getFruitX(),
                                           fruit->getFruitY(),
                                           fruit->getTotalFruit())) > 0)
            {
                snakes[currSnake]->growUpSnake();
                fruit->refreshFruit(eattenFruitElement-1);
                Beep(5300, 10);
            }


            if (!snakes[currSnake]->amIDead())
                if ((snakeDiedReason[currSnake] = this->isSnakeInConflict(currSnake))
                        > 0)
                    snakes[currSnake]->setMeDead();

            // TODO (tomas#1#): If all snakes Die, stop time

            playerPoints[currSnake] = snakes[currSnake]->getSnakeLength() * SCORE_MULTIPLIER;
            playerStats[currSnake] = "Player " + players[currSnake]->getPlayerName() + " Points: " + std::to_string(playerPoints[currSnake]) +
                                     (snakes[currSnake]->amIDead() ? " Dead by " + deads.at(snakeDiedReason[currSnake]) : "");

        } // current snake

        graphic->redrawVideoBuffer();

        // print player stats
        for (int i = 0; i < 4; i++)
            graphic->coutVCentered(playerStats[i]);

        // print elapsed time
        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time=
            (this->end_time - this->start_time) / 1000;

        graphic->coutVCentered("Duration: "
              + std::to_string((int)this->elapsed_time.count()) + "s");

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

//! \brief  Is controlling Snake conflict with environment
//!
//! \param  current element number of Snake instance
//! \return 1 wall, 2 itself, 3 foreign snake conflict
//!
//!
int Process::isSnakeInConflict(int currSnake)
{
    // hitting wall check
    if ( snakes[currSnake]->getSnakeXHead() == 0 ||
            snakes[currSnake]->getSnakeXHead() == field->getFieldWidth()-1 ||
            snakes[currSnake]->getSnakeYHead() == 0 ||
            snakes[currSnake]->getSnakeYHead() == field->getFieldHeight()-1
       )
    {
        return 1;
    }

    // hitting itsefl check
    for (int tail = 1; tail < snakes[currSnake]->getSnakeLength(); tail++)
    {
        if (snakes[currSnake]->getSnakeXHead() == snakes[currSnake]->getSnakeX()[tail] &&
                snakes[currSnake]->getSnakeYHead() == snakes[currSnake]->getSnakeY()[tail]
           )
        {
            return 2;
        }
    }

    // looking for foreign snake instance
    for (int foreignSnake = 0; foreignSnake < totalPlayers; foreignSnake++)
    {
        // looking for foreign snake tail
        for (int tail = 0; tail < snakes[foreignSnake]->getSnakeLength(); tail++)
        {
            if (currSnake != foreignSnake) // if not the same Snake
            {
                if (    snakes[currSnake]->getSnakeXHead() == snakes[foreignSnake]->getSnakeX()[tail] &&
                        snakes[currSnake]->getSnakeYHead() == snakes[foreignSnake]->getSnakeY()[tail] )
                {
                    // eats each other
                    return 3;
                }
            }
        }
    }

    // no conflict
    return 0;
}



bool Process::isGaming() const
{
    return this->isGamingContinue;
}
