#pragma once
#include "Field.h"
#include "Snake.h"
#include "Fruit.h"
#include "Graphics.h"
#include "Keyboard.h"

#include <chrono>
#include <string>

class Process
{
    Field* field;
    Snake* snake;
    Fruit* fruit;
    Graphics* graphics;
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
