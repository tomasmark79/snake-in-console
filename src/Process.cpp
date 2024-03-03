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

Process::Process(int width, int height)
:totalPoints(0), totalCycles(0), isNextGameWantedValue(true)
{
    field = new Field(width, height);
    snake = new Snake(*field);
    fruit = new Fruit(*field);
    graphics = new Graphics(*field);
    this->mainLoop();
}

Process::~Process()
{
    delete graphics;
    delete fruit;
    delete snake;
    delete field;
}

const void Process::mainLoop()
{
    int eattenFruitElement = 0;
    int gameOverReason = 0;

    this->start_time =
        std::chrono::high_resolution_clock::now();

    while (true)
    {
        int keyboardCode = keyboard.getMyKeyboardCode();

        graphics->clearVideoBuffer();

        // wall
        graphics->addWallsToVideoBuffer();

        // fruit
        graphics->addFruitToVideoBuffer(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        // snake
        snake->setSnakeDirectionAndShift(keyboardCode);
        graphics->addSnakeToVideoBuffer(
            snake->getSnakeX(),
            snake->getSnakeY(),
            snake->getSnakeLength());
        graphics->redrawVideoBuffer();
        if ( (eattenFruitElement = snake->getElementOfEattenFruit(
                                       fruit->getFruitX(),
                                       fruit->getFruitY(),
                                       fruit->getTotalFruit())) > 0)
        {
            snake->growUpSnake();
            fruit->refreshFruit(eattenFruitElement-1);
            Beep(5300, 40);
        }

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
        gameOverReason = snake->isSnakeInConflict();
        if (gameOverReason == 1 || gameOverReason == 2)
        {
            graphics->coutGOver(gameOverReason);
            break;
        }

        // retarder
        std::this_thread::sleep_for(150ms);

        // time calc
        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time=
            (this->end_time - this->start_time) / 1000;

        // player information
        totalPoints = snake->getSnakeLength() * SCORE_MULTIPLIER;
        msg = "Points: " + std::to_string(this->totalPoints) +
        " Elapsed: " + std::to_string((int)this->elapsed_time.count()) + "s";
        graphics->coutVCentered(msg);
        graphics->coutVCentered("(H)elp | (R)estart | (P)ause | e(X)it");
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
