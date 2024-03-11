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
#include <vector>

static const short SCORE_MULTIPLIER = 11;
class Process
{
    Keyboard keyboard;
    int totalPlayers;

    std::shared_ptr<Field> field;
    std::unique_ptr<Fruit> fruit;
    std::unique_ptr<Graphic> graphic; // Graphic* Graphic
    std::unique_ptr<std::unique_ptr<Player>[]> players; // Player** players
    std::unique_ptr<std::shared_ptr<Snake>[]> snakes; // Snakes**

    std::string msg;
    bool isGamingContinue;

    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    std::chrono::duration<double, std::milli> elapsed_time;

public:
    Process(int width,
            int height,
            double fruitEmptiness,
            int totalPlayers,
            std::string* playerNames
            );
    ~Process() = default;
    void mainLoop();
    bool isGaming() const;
};
