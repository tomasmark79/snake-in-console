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
#include <map>

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;
using std::string;

static const short SCORE_MULTIPLIER = 11;
static const short SNAKE_SPEED = 1;

class Process
{

    Keyboard keyboard;
    int totalPlayers;

    shared_ptr<Field> field;
    unique_ptr<Fruit> fruit;
    unique_ptr<Graphic> graphic; // Graphic* Graphic
    unique_ptr<unique_ptr<Player>[]> players; // Player** players
    unique_ptr<shared_ptr<Snake>[]> snakes; // Snakes**

    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    std::chrono::duration<double, std::milli> elapsed_time;

public:
    Process(int width,
            int height,
            double fruitEmptiness,
            int totalPlayers,
            string* playerNames
            );
    ~Process() = default;
    void mainLoop();
    void checkSnakeConflicts(int currSnake);

    bool isGameGoingOn;
    bool getIsGameGoingOn() const;
};
