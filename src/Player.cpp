#include "Player.h"

Player::Player()
{


}

Player::Player(int playerId, std::string playerName)
    : playerId(playerId), playerName(playerName)
{
}

Player::~Player()
{

}

const void Player::setPlayerName(std::string playerName)
{
    this->playerName = playerName;

}

const std::string Player::getPlayerName() const
{
    return this->playerName;
}
