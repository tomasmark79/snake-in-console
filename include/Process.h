//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include "Player.h"
#include "Snake.h"
#include "Fruit.h"
#include "Graphic.h"
#include "Keyboard.h"

#include <chrono>
#include <string>

static const short SCORE_MULTIPLIER = 11;
class Process
{
    Keyboard keyboard;
    int totalPlayers;

    std::unique_ptr<Field> field;
    std::unique_ptr<Fruit> fruit;
    std::unique_ptr<Graphic> graphic; // Graphic* Graphic
    std::unique_ptr<std::unique_ptr<Player>[]> players; // Snakes** snakes
    std::unique_ptr<std::unique_ptr<Snake>[]> snakes; // Player** players

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
