#include "Process.h"
#include <thread>   // std::this_thread::sleep_for
#include <iomanip>  // std::setprecision
#include <sstream>  // sstreamstring

using namespace std::chrono_literals;

Process::Process(int width, int height)
:isNextGameWantedValue(true)
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
    int totalCycles = 0;
    int eattenFruitElement = 0;
    int gameOverReason = 0;

    while (true)
    {
        this->start_time =
            std::chrono::high_resolution_clock::now();

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

        // retarder
        std::this_thread::sleep_for(150ms);

        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time =
            this->end_time - this->start_time;

        msg = "Points: " + std::to_string((snake->getSnakeLength() * SCORE_MULTIPLIER)) +
        " Duration: " + std::to_string(totalCycles++);
        graphics->coutVCentered(msg);

        graphics->coutVCentered("(H)elp | (R)estart | (P)ause | e(X)it");

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

        if (keyboardCode == 4)
        {
            this->isNextGameWantedValue = false;
            break;
        }
        if (keyboardCode == 5)
            graphics->coutHelp();

        gameOverReason = snake->isSnakeInConflict();
        if (gameOverReason == 1 || gameOverReason == 2)
        {
            graphics->coutGOver(gameOverReason);
            break;
        }
        if (keyboardCode == 6)
        {
            gameOverReason = 3;
            break;
        }
    }
}

const bool Process::isNextGameWanted() const
{
    return this->isNextGameWantedValue;
}
