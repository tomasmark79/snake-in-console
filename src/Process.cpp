//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Process.h"
#include <thread>   // std::this_thread::sleep_for
#include <iomanip>  // std::setprecision
#include <sstream>  // sstreamstring
#include <exception>

Process::Process(int width, int height, double fruitEmptiness,
                 int totalPlayers, string* playerNames/*, Network& net*/)
    : totalPlayers(totalPlayers),
      totalDeadPlayers(0),
      field(make_shared    <Field>   (width, height)),
      fruit(make_unique    <Fruit>   (fruitEmptiness, width, height)),
      graphic(make_unique  <Graphic> (width, height)),
      players(make_unique  <unique_ptr <Player> []> (totalPlayers + 1)),
      snakes(make_unique   <shared_ptr <Snake>  []> (totalPlayers + 1)),
      isGameGoingOn(true) /*,net(net)*/
{
    // spawn player's id and names
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        players[playerId] = make_unique<Player>(playerId, playerNames[playerId]);
        snakes[playerId] = make_unique<Snake>(playerId, SNAKE_SPEED, width, height, width/2, height/2);
    }

    this->mainLoop();
}

Process::~Process()
{
    snakes.reset();
    players.reset();
    graphic.reset();
    fruit.reset();
    field.reset();
}

void Process::mainLoop()
{
    int eattenFruitElement = 0;
    int playerPoints[4] = {0,0,0,0};
    std::string playerStats[4] = {"","","",""};

    std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::high_resolution_clock::now();

    Keyboard keyboard;

    while (true)
    {
        std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_time = (end_time - start_time) / 1000;



        int playerInput[4] = {-1,-1,-1,-1};
        int keyboardCode = keyboard.getMyKeyboardCode();

        // split keybord input to players
        if (keyboardCode >= 10 && keyboardCode <=13)
            playerInput[0] = keyboardCode - 10;
        else if (keyboardCode >= 20 && keyboardCode <=23)
            playerInput[1] = keyboardCode - 20;
        else if (keyboardCode >= 30 && keyboardCode <=33)
            playerInput[2] = keyboardCode - 30;
        else if (keyboardCode >= 40 && keyboardCode <=43)
            playerInput[3] = keyboardCode - 40;

        // clear
        graphic->clearVideoBuffer();

        // wall
        graphic->addWallsToVideoBuffer();

        // fruit
        graphic->addFruitToVideoBuffer(
            fruit->getFruitX(),
            fruit->getFruitY(),
            fruit->getTotalFruit());

        // go through snakes
        for (int currSnake = 0; currSnake < this->totalPlayers; currSnake ++)
        {
            // Snake direction and movement and buffer filling
            snakes[currSnake]->setMyDirectionAndShift(playerInput[currSnake]);

            graphic->addSnakeToVideoBuffer(currSnake,
                                           snakes[currSnake]->getX(),
                                           snakes[currSnake]->getY(),
                                           snakes[currSnake]->getLength(),
                                           snakes[currSnake]->getIsDead());

            if ( (eattenFruitElement     = snakes[currSnake]->getElementOfEattenFruit(
                                               fruit->getFruitX(),
                                               fruit->getFruitY(),
                                               fruit->getTotalFruit())) > 0)
            {
                snakes[currSnake]->growUp();
                fruit->refreshFruit(eattenFruitElement-1);
                Beep(5300, 10);
            }

            this->checkSnakeConflicts(currSnake);

            playerPoints[currSnake] = snakes[currSnake]->getLength() * SCORE_MULTIPLIER;
            playerStats[currSnake] = "Player with Snake "
                                     + players[currSnake]->getPlayerName()
                                     + " Points: " + std::to_string(playerPoints[currSnake])
                                     + (snakes[currSnake]->getIsDead()
                                        ? " was killed by " + snakes[currSnake]->getDeadDescripion()
                                        : " lives");


        } // go through snakes end

        graphic->redrawVideoBuffer();

        // print stats
        for (int i = 0; i < 4; i++)
        graphic->coutVCentered(playerStats[i]);
        graphic->coutVCentered("Duration: " +
        std::to_string((int)elapsed_time.count()) + "s");
        graphic->coutVCentered("(H)elp | (R)estart | e(X)it");

        // all players dead
        if (totalDeadPlayers == totalPlayers)
        {
            graphic->coutGameOver();
            break;
        }

        // restart game
        if (keyboardCode == 6)
            break;

        if (keyboardCode == 4)
        {
            this->isGameGoingOn = false;
            break;
        }

        // help game
        if (keyboardCode == 5)
            graphic->coutHelp();

        // sleep interval in ms
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

//! \brief  Check Snake conflict with environment
//!
//! \param  Current element number of Snake instance
//! \return 1 wall, 2 itself, 3 foreign snake conflict
//!
//!
// TODO (tomas#1#): Required remove returns, but mixed condition can occur
void Process::checkSnakeConflicts(int currSnake)
{
    if (snakes[currSnake]->getIsDead())
        return;

    // hitting wall check
    if (    snakes[currSnake]->getXHead() == 0 ||
            snakes[currSnake]->getXHead() == field->getFieldWidth()-1 ||
            snakes[currSnake]->getYHead() == 0 ||
            snakes[currSnake]->getYHead() == field->getFieldHeight()-1
       )
    {
        snakes[currSnake]->setDeadAndCode(1);
        totalDeadPlayers++;
        return;
    }

    // hitting itsefl check
    for (int tail = 1; tail < snakes[currSnake]->getLength(); tail++)
    {
        if (    snakes[currSnake]->getXHead() == snakes[currSnake]->getBackupX()[tail] &&
                snakes[currSnake]->getYHead() == snakes[currSnake]->getBackupY()[tail]
           )
        {
            snakes[currSnake]->setDeadAndCode(2);
            totalDeadPlayers++;
            return;
        }
    }

    // looking for foreign snake instance
    for (int foreignSnake = 0; foreignSnake < totalPlayers; foreignSnake++)
    {
        // looking for foreign snake tail
        for (int tail = 0; tail < snakes[foreignSnake]->getLength(); tail++)
        {
            if (currSnake != foreignSnake && !snakes[foreignSnake]->getIsDead()) // if not the same Snake and isNotDead
            {
                if (    snakes[currSnake]->getXHead() == snakes[foreignSnake]->getBackupX()[tail] &&
                        snakes[currSnake]->getYHead() == snakes[foreignSnake]->getBackupY()[tail] )
                {
                    // eats each other
                    snakes[currSnake]->setDeadAndCode(3);
                    totalDeadPlayers++;
                    return;
                }
            }
        }
    }
}

bool Process::getIsGameGoingOn() const
{
    return this->isGameGoingOn;
}
