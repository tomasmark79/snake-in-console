//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Game.h"
#include "Graphic.h"
#include "NetworkManager.h" // https://github.com/tomasmark79/server-client
#include <cctype> // tolower
#include <iostream>
#include <random>
#include <ctime>

constexpr int               MAX_PLAYERS = 4;
constexpr int               PLAYER_ANSWER_TRESHHOLD = 5; // give 5 attempts for user to enter right values
std::string playerNames    [MAX_PLAYERS];

const std::string_view userfailed = "\n\nGame needs your correct inputs.\n\n";
template<typename T1>
T1 getNumericAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold)
{
    T1 value = 0;
    int totalAnswers = 0;
    do
    {
        if (totalAnswers == attemptTreshold)
        {
            std::cout << userfailed;
            throw std::runtime_error(userfailed.data());
        }
        std::cout << question;
        std::cin >> value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(value < min || value > max);
    return value;
}

std::string getStringAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold)
{
    std::string answer = "";
    int totalAnswers = 0;
    do
    {
        if (totalAnswers == attemptTreshold)
        {
            std::cout << userfailed;
            throw std::runtime_error(userfailed.data());
        }
        std::cout << question;
        std::cin >> answer;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(static_cast<int>(answer.length()) < min || static_cast<int>(answer.length()) > max);
    return answer;
}

bool isAnswerYes(std::string question)
{
    if (std::tolower((question.substr(0, 3) == "yes")) ||
            std::tolower((question.substr(0, 2) == "ye")) ||
            std::tolower((question.substr(0, 1) == "y")) )
        return true;
    return false;
}

int main()
{

    // // // // // // // // // // // // // // // // // // // // //
    NetworkManager net;
    vector<int> eraryVector;
    bool isMultiplayerActive = false;
    // // // // // // // // // // // // // // // // // // // // //

    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << getAppBanner();
    int totalPlayers = MAX_PLAYERS;
    playerNames[0] = "Snake 1";
    playerNames[1] = "Snake 2";
    playerNames[2] = "Snake 3";
    playerNames[3] = "Snake 4";
    int fieldWidth      = 50;
    int fieldHeight     = 25;
    int fruitEmptiness  = 3.5;  // more is less fruit

    // int networkPlayers  = 0;

    std::string isUDPMultiplayer = getStringAnswerFromPlayer("Do you want to play multiplayer over network? y/n: ", 1, 3, PLAYER_ANSWER_TRESHHOLD);
    if (isAnswerYes(isUDPMultiplayer))
    {
        isMultiplayerActive = true;
        totalPlayers = 2;
        // Network Multiplayer
        std::cout << "Network multiplayer: enabled" << std::endl;
        std::string isThisGameSessionServer = getStringAnswerFromPlayer("Do you want to HOST network game? y/n: ", 1, 3, PLAYER_ANSWER_TRESHHOLD);
        if (isAnswerYes(isThisGameSessionServer))
        {
            // Server Session
            std::cout << "Server session started ... " << std::endl;
            net
            .setIsServer(true)
            .setBindHostName("192.168.79.101")
            .setBindPort(7996)
            .setMaxClients(4)
            .setChannels(2)
            .setAmountIn(0)
            .setAmountOut(0);
            net.initENet();
            net.registerClients(1000, 10);
        }
        else
        {
            // Client Session
            std::cout << "Client session started ... " << std::endl;
            net
            .setIsServer(false)
            .setRemoteHostName("192.168.79.101")
            .setRemotePort(7996)
            .setOutConnections(1);
            net.initENet();
            net.registerServer(1000, 10);
        }
    }
    else
    {
        std::string isHotSeatMultiplayer = getStringAnswerFromPlayer("Do you want to play HOT-SEAT game? (up to 2 players) y/n: ", 1, 3, PLAYER_ANSWER_TRESHHOLD);
        // Single player or hot seat
        if (isAnswerYes(isHotSeatMultiplayer))
        {
            std::string isRequestedCustomProperties = getStringAnswerFromPlayer("Do you want to modify default settings? y/n: ", 1, 3, PLAYER_ANSWER_TRESHHOLD);
            if (isAnswerYes(isRequestedCustomProperties))
            {
                // Custom properties to set by user
                totalPlayers = 1;
                playerNames[0] = getStringAnswerFromPlayer("Enter name of your Snake ? ", 2, 20, PLAYER_ANSWER_TRESHHOLD);
                fieldWidth = getNumericAnswerFromPlayer<int>("Enter width of space area. (min 15 recomended 80) ?: ", 20, 360, PLAYER_ANSWER_TRESHHOLD);
                fieldHeight = getNumericAnswerFromPlayer<int>("Enter height of space area. (min 10 recomended 35) ?: ", 10, 360, PLAYER_ANSWER_TRESHHOLD);
                fruitEmptiness = getNumericAnswerFromPlayer<double>("Enter fruit emptiness (min 0.1, max 10) ?: ", 0.1, 10, PLAYER_ANSWER_TRESHHOLD);
            }
            else
            {
                // Default properties for singleplayer
                totalPlayers = 1;
            }

            // Hot Seat Session
            totalPlayers = getNumericAnswerFromPlayer<int>("Enter number of player. 1-4 ?: ", 1, 4, PLAYER_ANSWER_TRESHHOLD);
            for (int playerId = 0; playerId < totalPlayers; playerId++)
                playerNames[playerId] = getStringAnswerFromPlayer("Enter name of " + playerNames[playerId] + " ?: ", 2, 20, PLAYER_ANSWER_TRESHHOLD);

        }
        else
        {
            // Single Player Session
            std::string isRequestedCustomProperties = getStringAnswerFromPlayer("Do you want to specify size of snake area and other settings? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
            if (isAnswerYes(isRequestedCustomProperties))
            {
                // Custom properties to set by user
                totalPlayers = 1;
                playerNames[0] = getStringAnswerFromPlayer("Enter name of your Snake ? ", 2, 20, PLAYER_ANSWER_TRESHHOLD);
                fieldWidth = getNumericAnswerFromPlayer<int>("Enter width of space area. (min 15 recomended 80) ?: ", 20, 360, PLAYER_ANSWER_TRESHHOLD);
                fieldHeight = getNumericAnswerFromPlayer<int>("Enter height of space area. (min 10 recomended 35) ?: ", 10, 360, PLAYER_ANSWER_TRESHHOLD);
                fruitEmptiness = getNumericAnswerFromPlayer<double>("Enter fruit emptiness (min 0.1, max 10) ?: ", 0.1, 10, PLAYER_ANSWER_TRESHHOLD);
            }
            else
            {
                // Default properties for singleplayer
                totalPlayers = 1;
            }
        }
    }

    while(true)
    {
        Game gameSnake(fieldWidth, fieldHeight, fruitEmptiness, totalPlayers, playerNames, net, isMultiplayerActive);
        if (!gameSnake.getIsGameGoingOn())
            break;
    }
    return 0;

}
