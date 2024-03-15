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
#include "Network.h"
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

    Network& net;

public:
    Process(int width,
            int height,
            double fruitEmptiness,
            int totalPlayers,
            string* playerNames,
            Network& net
           );

    ~Process();

    // return copy of serialized snake coords
    vector<int> serializeSnakeCoords(int currSnake)
    {
        vector<int> head{0x5};
        vector<int> v_x{};
        vector<int> v_y{};
        for (int i = 0; i < snakes[currSnake]->getLength(); i++)
        {
            v_x.push_back(snakes[currSnake]->getX()[i]);
            v_y.push_back(snakes[currSnake]->getY()[i]);
        }
        vector<int> serialized{};
        serialized.reserve(head.size() + v_x.size() + v_y.size());
        serialized.insert(serialized.end(), head.begin(), head.end());
        serialized.insert(serialized.end(), v_x.begin(), v_x.end());
        serialized.insert(serialized.end(), v_y.begin(), v_y.end());
        return serialized;
    }

    void mainLoop();
    void checkSnakeConflicts(int currSnake);

    bool isGameGoingOn;
    bool getIsGameGoingOn() const;
};
