#include "Process.h"
#include "Compiler.h"
#include <thread>   // std::this_thread::sleep_for
#include <iomanip>  // std::setprecision
#include <sstream>  // sstreamstring

using namespace std::chrono_literals;

Process::Process(int width, int height)
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
    int cycleCounter = 0;
    int gameOverReason = 0;
    int fruitEattenIndex = 0;

    while (true)
    {
        int snakeCommand =
            keyboard.getMyKeyboardCode();

        this->start_time =
            std::chrono::high_resolution_clock::now();

        graphics->clearBuffer();
        graphics->addWallsToBuffer();

        if (snakeCommand == 5)
            graphics->printHelp();

        if (snakeCommand == 6)
        {
            gameOverReason = 3;
            break;
        }

        graphics->addFruitToBuffer(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        snake->setSnakeWay(snakeCommand);

        graphics->addSnakeToBuffer(
            snake->getSnakeX(),
            snake->getSnakeY(),
            snake->getSnakeLength());

        graphics->redrawBuffer();

        gameOverReason = snake->checkSnakeConflict();
        if (gameOverReason == 1 || gameOverReason == 2)
            break;

        fruitEattenIndex = snake->whichFruitSnakeEatten(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        if (fruitEattenIndex > 0)
            {
                snake->addTail();
                fruit->refreshFruit(fruitEattenIndex-1);
                Beep(5300, 40);
            }


        this->end_time =
            std::chrono::high_resolution_clock::now();
        this->elapsed_time =
            this->end_time - this->start_time;

        // set precision
        std::ostringstream _stream;
        _stream << std::fixed << std::setprecision(1) << this->elapsed_time.count();

        msg =
            "Snake X: " + std::to_string(snake->getSnakeX()[0]) +
            " Y: " + std::to_string(snake->getSnakeY()[0]) +
            " Fruit X: " + std::to_string(fruit->getFruitX()[0]) +
            " Y: " + std::to_string(fruit->getFruitY()[0]) +
            " Length: " + std::to_string(snake->getSnakeLength() + 1) +
            " Direction: " + std::to_string(snake->getSnakeDirection()) +
            " T: " + _stream.str() + "ms" +
            " C: " + std::to_string(cycleCounter++);
        graphics->printInfo(msg);
        graphics->printInfo("Press key H for help | Press ctrl+break to exit | Press ctrl+c for no action");

        // retarder
        std::this_thread::sleep_for(150ms);
    }

    graphics->prntGameOver(gameOverReason);
}

