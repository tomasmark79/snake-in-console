//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <string>
using std::string;

class Player
{
    int playerId;
    string playerName;
public:
    Player(int playerId, string playerName)
        : playerId(playerId), playerName(playerName) {};
    void setPlayerName(string playerName)
    {
        this->playerName = playerName;
    };
    string getPlayerName() const{
    return this->playerName;
    };
};

