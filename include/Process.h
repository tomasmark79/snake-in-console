#pragma once
#include "Graphics.h"
#include "Snake.h"
#include "Keyboard.h"
#include <chrono>
#include <string>
class Process
{
    Graphics* graphics;
    Snake* snake;
    Keyboard keyboard;
    std::string msg;
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    std::chrono::duration<double, std::milli> elapsed_time;
public:
    Process(int width, int height);
    ~Process();
    const void mainLoop();
};
