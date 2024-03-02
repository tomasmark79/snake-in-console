#include "Process.h"
#include "Compiler.h"
#include <thread>       // std::this_thread::sleep_for
#include <iomanip>
#include <sstream>

using namespace std::chrono_literals;

Process::Process(int width, int height)
{
    field = new Field(width, height);
    snake = new Snake(*field);
    graphics = new Graphics(*field);
    this->mainLoop();
}

Process::~Process()
{
    delete graphics;
    delete snake;
    delete field;
}

const void Process::mainLoop()
{
    int cCounter = 0;
    int gameOverReason = 0;

    while (true)
    {
        int snakeCommand = keyboard.getMyKeyboardCode();

        this->start_time = std::chrono::high_resolution_clock::now();

        // TO DO
        // temporary hack due no fruits yet
        if (snakeCommand == 4)
            snake->addTail();

        if (snakeCommand == 5)
            graphics->printHelp();

        if (snakeCommand == 6)
        {
            gameOverReason = 3;
            break;
        }

        graphics->clearBuffer();
        graphics->addWallsToBuffer();

        snake->setSnakeWay(snakeCommand);

        graphics->addSnakeToBuffer(
            snake->getSnakeX(),
            snake->getSnakeY(),
            snake->getSnakeLength());

        graphics->redrawBuffer();

        gameOverReason = snake->getSnakeConflict();
        if (gameOverReason == 1 || gameOverReason == 2)
            break;

        this->end_time = std::chrono::high_resolution_clock::now();
        this->elapsed_time = this->end_time - this->start_time;

        // set precision
        std::ostringstream _stream;
        _stream << std::fixed << std::setprecision(1) << this->elapsed_time.count() ;

        msg =
            "Snake X: " + std::to_string(snake->getSnakeX()[0]) +
            " Y: " + std::to_string(snake->getSnakeY()[0]) +
            " Length: " + std::to_string(snake->getSnakeLength() + 1) +
            " Direction: " + std::to_string(snake->getSnakeDirection()) +
            " Retarder: " + _stream.str() + "ms" +
            " Cycle: " + std::to_string(cCounter++);
        graphics->prntVrtCenText(graphics->getScreenHeight(),msg);
        graphics->prntVrtCenText(graphics->getScreenHeight() + 1,
                                 "Press key H for help | Press ctrl+break to exit | Press ctrl+c for no action");

        // retarder
        std::this_thread::sleep_for(150ms);
    }
    graphics->prntGameOver(gameOverReason);
}

