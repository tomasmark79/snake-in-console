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
    Player();
    Player(int playerId, std::string playerName);
    virtual ~Player();
    const void setPlayerName(std::string playerName);
    const std::string getPlayerName() const;
};

