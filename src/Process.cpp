#include "Process.h"
#include "Compiler.h"
#include <thread>       // std::this_thread::sleep_for
#include <iomanip>
#include <sstream>

using namespace std::chrono_literals;

Process::Process(int width, int height)
{
    graphics = new Graphics(width, height);
    snake = new Snake(width, height);
    this->mainLoop();
}

Process::~Process()
{
    delete graphics;
    delete snake;
}

const void Process::mainLoop()
{
    int cCounter = 0;

    while (true)
    {
        this->start_time = std::chrono::high_resolution_clock::now();

        graphics->clearBuffer();
        graphics->addWallsToBuffer();

        int snakeCommand = keyboard.getMyKeyboardCode();

        snake->setSnakeWay(snakeCommand);

        // TO DO
        // temporary hack due no fruits yet
        if (snakeCommand == 4)
            snake->addTail();

        graphics->addSnakeToBuffer(
            snake->getSnakeX(),
            snake->getSnakeY(),
            snake->getSnakeLength());

        graphics->redrawBuffer();

        this->end_time = std::chrono::high_resolution_clock::now();
        this->elapsed_time = this->end_time - this->start_time;

        // set precision
        std::ostringstream _stream;
        _stream << std::fixed << std::setprecision(1) << this->elapsed_time.count() ;

        msg =
            Compiler().getCppCompilerV() +
            " Snake X: " + std::to_string(snake->getSnakeX()[0]) +
            " Y: " + std::to_string(snake->getSnakeY()[0]) +
            " Length: " + std::to_string(snake->getSnakeLength() + 1) +
            " Direction: " + std::to_string(snake->getSnakeDirection()) +
            " Retarder: " + _stream.str() + "ms" +
            " Cycle: " + std::to_string(cCounter++) + "\n";


        graphics->printInfo(msg);

        std::this_thread::sleep_for(150ms);

    }
}

