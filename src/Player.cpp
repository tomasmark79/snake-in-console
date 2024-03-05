#include "Player.h"
#include "conio.h" // _kbhit && _getch

Player::Player(int playerId, std::string playerName)
    : playerId(playerId), playerName(playerName)
{
}

Player::~Player()
{

}

const std::string Player::getPlayerName() const
{
    return this->playerName;
}
