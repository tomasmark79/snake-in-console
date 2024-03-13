//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Process.h"
#include "Graphic.h"
#include "Network.h"
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

bool isAnswerYes(string question)
{
    if (std::tolower((question.substr(0, 3) == "yes")) ||
            std::tolower((question.substr(0, 2) == "ye")) ||
            std::tolower((question.substr(0, 1) == "y")) )
        return true;
    return false;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::cout << getAppBanner();
    int totalPlayers = MAX_PLAYERS;
    playerNames[0] = "Snake 1";
    playerNames[1] = "Snake 2";
    playerNames[2] = "Snake 3";
    playerNames[3] = "Snake 4";
    int fieldWidth      = 80;
    int fieldHeight     = 35;
    int fruitEmptiness  = 3.5;  // more is less fruit

    int networkPlayers  = 0;

    Network net; // isNetworkActive false by default

    string isUDPMultiplayer = getStringAnswerFromPlayer("Do you want to play multiplayer game over network? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
    if (isAnswerYes(isUDPMultiplayer))
    {
        // Network Multiplayer
        cout << "Network multiplayer: enabled" << endl;
        string isThisGameSessionServer = getStringAnswerFromPlayer("Do you want to HOST multiplayer game for other players? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
        if (isAnswerYes(isThisGameSessionServer))
        {
            // Server Session
            net.setIsNetworkActive(true);
            net.setIsServerActive(true);
            net.setHostName("192.168.79.101");
            net.setPort(7999);
            net.setClients(4); // todo via totalPlayers
            net.setChannels(2);
            net.setAmountIn(0);
            net.setAmountOut(0);
            net.initENet();
            net.initServer();

            cout << endl << "Waiting for other players 5 sec..." << endl;
            const time_t startTime = time(nullptr);
            while (time(nullptr) - startTime < 10)
            {
                if (net.hostService() == 1)
                    networkPlayers++;
            }
            std::cout << "Connected " << networkPlayers << " players." << endl;
            if (networkPlayers == 0)
                return 0;

            // how many networkPlayer how many Snakes
            totalPlayers = networkPlayers + 1 /* +1 player is server */;
            // Run Server and takes client to the game
        }
        else
        {
            // Client Session
            net.setIsNetworkActive(true);
            net.setIsServerActive(false);
            net.setHostName("192.168.79.101");
            net.setPort(7999);
            net.setOutConnections(1);
            net.setChannels(2);
            net.setAmountIn(0);
            net.setAmountOut(0);
            net.initENet();
            net.initClient();

            cout << endl << "Connecting to host ..." << endl;
            const time_t startTime = time(nullptr);
            while (time(nullptr) - startTime < 20)
            {
                if (net.connectToHost() == 0)
                    break;
            }
            cout << "Connected to host " << net.getHostName() << ":" << net.getPort() << "." << endl;
        }
    }
    else
    {
        string isHotSeatMultiplayer = getStringAnswerFromPlayer("Do you want to play HOT SEAT multiplayer game at one keyboard? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
        // Single player or hot seat
        if (isAnswerYes(isHotSeatMultiplayer))
        {
            // Hot Seat Session
            totalPlayers = getNumericAnswerFromPlayer<int>("Enter number of player. 1-4 ? ", 1, 4, PLAYER_ANSWER_TRESHHOLD);
            for (int playerId = 0; playerId < totalPlayers; playerId++)
                playerNames[playerId] = getStringAnswerFromPlayer("Enter name of " + playerNames[playerId] + " ?", 2, 20, PLAYER_ANSWER_TRESHHOLD);

        }
        else
        {
            // Single Player Session
            string isRequestedCustomProperties = getStringAnswerFromPlayer("Do you want to specify size of snake area and other settings? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
            if (isAnswerYes(isRequestedCustomProperties))
            {
                // Custom properites to set by user
                totalPlayers = 1;
                playerNames[0] = getStringAnswerFromPlayer("Enter name of your Snake ? ", 2, 20, PLAYER_ANSWER_TRESHHOLD);
                fieldWidth = getNumericAnswerFromPlayer<int>("Enter width of space area. (min 15 recomended 80) ? ", 20, 360, PLAYER_ANSWER_TRESHHOLD);
                fieldHeight = getNumericAnswerFromPlayer<int>("Enter height of space area. (min 10 recomended 35) ? ", 10, 360, PLAYER_ANSWER_TRESHHOLD);
                fruitEmptiness = getNumericAnswerFromPlayer<double>("Enter fruit emptiness (min 0.1 recomended 3.5) ? ", 0.1, 10, PLAYER_ANSWER_TRESHHOLD);
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
        Process gameSnake(fieldWidth, fieldHeight, fruitEmptiness, totalPlayers, playerNames, net);
        if (!gameSnake.getIsGameGoingOn())
            break;
    }
    return 0;




//    if ( net.initENet() != 0)
//    {
//        // fprintf (stderr, "An error occurred while initializing ENet.\n");
//        cout << "An error occurred while initializing ENet.\n" << std::endl;
//        return EXIT_FAILURE;
//    }
//    atexit (enet_deinitialize);
//
//
//    // Server/Client
//    string serverOrClient = getStringAnswerFromPlayer("Host game? yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);
//    if (serverOrClient.compare(0, 3, "yes") == 0 || serverOrClient.compare(0, 2, "ye") == 0 || serverOrClient.compare(0, 1, "y") == 0)
//    {
//        // Server
//        net.setIsServerActive(true);
//        isGameInServerMode = true;
//        net.initServer("192.168.79.101", 7999, 4, 2, 0, 0);
//    }
//    else
//    {
//        net.setIsServerActive(false);
//        net.initClient("192.168.79.101", 7999, 1,2,0,0);
//    }
//
//    // cout << res << endl;



//    // or user can create custom game
//    if (yesOrNo.compare(0, 3, "yes") == 0 || yesOrNo.compare(0, 2, "ye") == 0 || yesOrNo.compare(0, 1, "y") == 0)
//    {
//        ;
//    }
//    else
//    {
//        // question 1
//        totalPlayers = getNumericAnswerFromPlayer<int>("Enter number of player 1-4 ? ", 1, 4, PLAYER_ANSWER_TRESHHOLD);
//        // question 2
//        for (int playerId = 0; playerId < totalPlayers; playerId++)
//            playerNames[playerId] = getStringAnswerFromPlayer("Enter name of Snake ? ", 2, 20, PLAYER_ANSWER_TRESHHOLD);
//
//        // question 3
//        fieldWidth = getNumericAnswerFromPlayer<int>("Enter width of field. (min 20 recomended 80) ? ", 20, 360, PLAYER_ANSWER_TRESHHOLD);
//
//        // quesrion 4
//        fieldHeight = getNumericAnswerFromPlayer<int>("Enter width of heihgt. (min 10 recomended 35) ? ", 10, 360, PLAYER_ANSWER_TRESHHOLD);
//
//        // quesrion 5
//        fruitEmptiness = getNumericAnswerFromPlayer<double>("Enter fruit emptiness (min 1 recomended 2.5) ? ", 1, 10, PLAYER_ANSWER_TRESHHOLD);
//    }

// Start Game
}





