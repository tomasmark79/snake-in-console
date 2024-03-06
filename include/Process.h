//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include "Player.h"
#include "Snake.h"
#include "Fruit.h"
#include "Graphics.h"
#include "Keyboard.h"

#include <chrono>
#include <string>

static const short SCORE_MULTIPLIER = 11;
class Process
{

//    int totalPointsSnake1;
//    int totalPointsSnake2;
//
//    int gameOverReasonSnake1;
//    int gameOverReasonSnake2;
//
//    int totalCycles;

    Field* field;
    int totalPlayers;
    Player** players;
    Snake** snakes;
    Fruit* fruit;
    Graphics* graphics;
    Keyboard keyboard;

    std::string msg;
    bool isNextGameWantedValue;

        std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    std::chrono::duration<double, std::milli> elapsed_time;



public:
    Process(int width, int height, double fruitEmptiness, int totalPlayers, std::string* playerNames);
    ~Process();
    const void mainLoop();
    const bool isNextGameWanted() const;

};
