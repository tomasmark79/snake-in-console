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
// #include "Network.h"
#include <map>

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;
using std::string;
using std::vector;

static const int SCORE_MULTIPLIER = 11;
static const int SNAKE_SPEED = 1;

class Process
{
    int totalPlayers;
    int totalDeadPlayers;
    shared_ptr<Field> field;
    unique_ptr<Fruit> fruit;
    unique_ptr<Graphic> graphic; // Graphic* Graphic
    unique_ptr<unique_ptr<Player>[]> players;
    unique_ptr<shared_ptr<Snake> []> snakes;

    // Network& net;

public:
    Process(int width,
            int height,
            double fruitEmptiness,
            int totalPlayers,
            string* playerNames /*, Network& net */
           );

    ~Process();

    void mainLoop();
    void checkSnakeConflicts(int currSnake);

    bool isGameGoingOn;
    bool getIsGameGoingOn() const;
};
