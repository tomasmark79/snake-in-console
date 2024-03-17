//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <string>

class Player
{
    int playerId;
    std::string playerName;
public:
    Player(int playerId, std::string playerName)
        : playerId(playerId), playerName(playerName) {};

    void setPlayerName(std::string playerName)
    {
        this->playerName = playerName;
    };

    std::string getPlayerName() const
    {
        return this->playerName;
    };
};

