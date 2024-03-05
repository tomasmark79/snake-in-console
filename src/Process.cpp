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

Process::Process(int width, int height, int totalPlayers, std::string& playerNames)
    : totalPlayers(totalPlayers), isNextGameWantedValue(true)
{
    field = new Field(width, height);
    fruit = new Fruit(*field);
    graphics = new Graphics(*field);

    players = new Player*[totalPlayers+1];
    snakes = new Snake*[totalPlayers+1];
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        players[playerId] = new Player(playerId, &playerNames[playerId]);
        snakes[playerId] = new Snake(playerId, *field);
        graphics->Cout(players[playerId]->getPlayerName());
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

//
//    this->start_time =
//        std::chrono::high_resolution_clock::now();
//
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
        }

        graphics->redrawVideoBuffer();




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

//
//        //
//        if (!snake1->isSnakeDie())
//        {
//            gameOverReasonSnake1 = snake1->isSnakeInConflict();
//            if (gameOverReasonSnake1 == 1 || gameOverReasonSnake1 == 2)
//            {
//                snake1->setSnakeDie();
//                // graphics->coutGOver(gameOverReason);
//                // break;
//            }
//        }
//
//        if (!snake2->isSnakeDie())
//        {
//            gameOverReasonSnake2 = snake2->isSnakeInConflict();
//
//            if (gameOverReasonSnake2 == 1 || gameOverReasonSnake2 == 2)
//            {
//                snake2->setSnakeDie();
//                // graphics->coutGOver(gameOverReason);
//                // break;
//            }
//        }
//
//        // retarder
        std::this_thread::sleep_for(150ms);
//
//        // time calc
//        this->end_time =
//            std::chrono::high_resolution_clock::now();
//        this->elapsed_time=
//            (this->end_time - this->start_time) / 1000;
//

//        // players information
//        totalPointsSnake1 = snake1->getSnakeLength() * SCORE_MULTIPLIER;
//        msg = "Snake 1 " + player1->getPlayerName() + " Points: " + std::to_string(this->totalPointsSnake1);
//        graphics->coutVCentered(msg);
//
//        totalPointsSnake2 = snake2->getSnakeLength() * SCORE_MULTIPLIER;
//        msg = "Snake 2 " + player2->getPlayerName() + " Points: " + std::to_string(this->totalPointsSnake2);
//        graphics->coutVCentered(msg);
//
//        msg = "Elapsed: "
//              + std::to_string((int)this->elapsed_time.count()) + "s";
//        graphics->coutVCentered(msg);
//
//        graphics->coutVCentered("(H)elp | (R)estart | (P)ause | e(X)it");
    }

}

// debug
//        // set precision
//        std::stringstream _stream;
//        _stream << std::fixed << std::setprecision(1) << this->elapsed_time.count();
//        msg =
//            "Snake X: " + std::to_string(snake->getSnakeX()[0]) +
//            " Y: " + std::to_string(snake->getSnakeY()[0]) +
//            " Fruit X: " + std::to_string(fruit->getFruitX()[0]) +
//            " Y: " + std::to_string(fruit->getFruitY()[0]);
//            graphics->coutVCentered(msg);
//
//        msg ="Length: " + std::to_string(snake->getSnakeLength() + 1) +
//            " Direction: " + std::to_string(snake->getSnakeDirection()) +
//            " T: " + _stream.str() + "ms" +
//            " C: " + std::to_string(totalCycles++);
//            graphics->coutVCentered(msg);




const bool Process::isNextGameWanted() const
{
    return this->isNextGameWantedValue;
}
