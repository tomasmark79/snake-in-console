//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "Process.h"
#include <thread>   // std::this_thread::sleep_for
#include <iomanip>  // std::setprecision
#include <sstream>  // sstreamstring


using namespace std::chrono_literals;

Process::Process(int width, int height, double fruitEmptiness, int totalPlayers, std::string* playerNames)
    : totalPlayers(totalPlayers), isNextGameWantedValue(true)
{
    field = new Field(width, height);
    fruit = new Fruit(fruitEmptiness, *field);
    graphics = new Graphics(*field);

    players = new Player*[totalPlayers+1];
    snakes = new Snake*[totalPlayers+1];
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        players[playerId] = new Player(playerId, playerNames[playerId]);
        snakes[playerId] = new Snake(playerId, *field);
    }

    this->mainLoop();
}

Process::~Process()
{
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        delete snakes[playerId];
        delete players[playerId];
    }
    delete snakes;
    delete players;

    delete graphics;
    delete fruit;
    delete field;
}

const void Process::mainLoop()
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

        graphics->clearVideoBuffer();

        // wall
        graphics->addWallsToVideoBuffer();

        // fruit
        graphics->addFruitToVideoBuffer(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        // go through sneakes
        for (int i = 0; i < this->totalPlayers; i ++)
        {

            if (!snakes[i]->isSnakeDie())
                snakes[i]->setSnakeDirectionAndShift(playerInput[i]);

            graphics->addSnakeToVideoBuffer(i,
                                            snakes[i]->getSnakeX(),
                                            snakes[i]->getSnakeY(),
                                            snakes[i]->getSnakeLength(),
                                            snakes[i]->isSnakeDie());


            if ( (eattenFruitElement = snakes[i]->getElementOfEattenFruit(
                                           fruit->getFruitX(),
                                           fruit->getFruitY(),
                                           fruit->getTotalFruit())) > 0)
            {
                snakes[i]->growUpSnake();
                fruit->refreshFruit(eattenFruitElement-1);
                Beep(5300, 10);
            }

            // conflict check
            if (!snakes[i]->isSnakeDie())
            {

                playerGameOverReason[i] = snakes[i]->isSnakeInConflict();
                if (playerGameOverReason[i] == 1 || playerGameOverReason[i] == 2)
                {
                    snakes[i]->setSnakeDie();
                    // graphics->coutGOver(gameOverReason);
                    // break;
                }
            }

            playerPoints[i] = snakes[i]->getSnakeLength() * SCORE_MULTIPLIER;
            playerStats[i] = "Player " + players[i]->getPlayerName() + " Points: " + std::to_string(playerPoints[i]) +
            (snakes[i]->isSnakeDie() ? " Dead " : "");
        }

        graphics->redrawVideoBuffer();

        // print player stats
        for (int i = 0; i < 4; i++)
            graphics->coutVCentered(playerStats[i]);

        // print elapsed time
        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time=
            (this->end_time - this->start_time) / 1000;

        msg = "Duration: "
              + std::to_string((int)this->elapsed_time.count()) + "s";
        graphics->coutVCentered(msg);
        graphics->coutVCentered("(H)elp | (R)estart | e(X)it");
        graphics->coutVCentered("Copyright (c) 2024 Tomas Mark");



        // exit game
        if (keyboardCode == 4)
        {
            this->isNextGameWantedValue = false;
            break;
        }

        // help game
        if (keyboardCode == 5)
            graphics->coutHelp();

        // restart game
        if (keyboardCode == 6)
            break;

        // retarder
        std::this_thread::sleep_for(150ms);

    }
}

const bool Process::isNextGameWanted() const
{
    return this->isNextGameWantedValue;
}
