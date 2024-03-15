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


    // position 0x00 command, 0x01 direction, 0x02 reserved
    vector<int> serialize(int command, int direction, int reserved)
    {
        vector<int> serialized{};
        serialized.reserve(4);
        serialized[0] = command;
        serialized[1] = direction;
        serialized[2] = reserved;

        return serialized;
    }
    // position 0x00 command, 0x01 direction, 0x02 reserved
    void deserialize(vector<int> serialized, int& command, int& direction, int& reserved)
    {
        serialized.reserve(4);
        command = serialized[0];
        direction = serialized[1];
        reserved = serialized[2];
    }


//    vector<int> serialize(int command, vector<int> vec1={}, vector<int> vec2={}, vector<int> vec3={})
//    {
//        vector<int> serialized{};
//        serialized.reserve(vec1.size() + 1 + vec2.size() + 1 + vec3.size() + 1);
//
//        serialized.insert(serialized.end(), vec1.size());
//        serialized.insert(serialized.end(), vec1.begin(), vec1.end());
//
//        serialized.insert(serialized.end(), vec2.size());
//        serialized.insert(serialized.end(), vec2.begin(), vec2.end());
//
//        serialized.insert(serialized.end(), vec3.size());
//        serialized.insert(serialized.end(), vec3.begin(), vec3.end());
//    }

//    vector<int> vec1;    vector<int> vec2;    vector<int> vec3;

//    vector<int> serializeSnakeCoords(int currSnake)
//    {
//        vector<int> head{0x5};
//        vector<int> v_x{};
//        vector<int> v_y{};
//        for (int i = 0; i < snakes[currSnake]->getLength(); i++)
//        {
//            v_x.push_back(snakes[currSnake]->getX()[i]);
//            v_y.push_back(snakes[currSnake]->getY()[i]);
//        }
//        vector<int> serialized{};
//        serialized.reserve(head.size() + v_x.size() + v_y.size());
//        serialized.insert(serialized.end(), head.begin(), head.end());
//        serialized.insert(serialized.end(), v_x.begin(), v_x.end());
//        serialized.insert(serialized.end(), v_y.begin(), v_y.end());
//        return serialized;
//    }

    void mainLoop();
    void checkSnakeConflicts(int currSnake);

    bool isGameGoingOn;
    bool getIsGameGoingOn() const;
};
