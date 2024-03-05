#pragma once
#include <string>


class Player
{
    int playerId;
    std::string playerName;

public:
    Player(int playerId, std::string playerName);
    virtual ~Player();
    const std::string getPlayerName() const;
};

