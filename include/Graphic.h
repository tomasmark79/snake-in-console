//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <string>

std::string getAppBanner();
std::string getGameOverBanner();

class Graphic
{
    int totalW;
    int totalH;
    char **videoBuffer; // C style pointer to an arrays int this class is the intent

public:
    Graphic(int totalW, int totalH);
    Graphic(const Graphic& other);
    Graphic& operator=(const Graphic& other);

    ~Graphic();

    void clearScreen() const;
    void clearVideoBuffer() const;
    void addWallsToVideoBuffer() const;
    void addSnakeToVideoBuffer
    (
        const int id,
        const int* x,
        const int* y,
        int snakeLength,
        bool isDie
    );
    void addFruitToVideoBuffer
    (
        const int* x,
        const int* y,
        int fruitElement
    );
    void redrawVideoBuffer() const;

    void Cout(std::string msg) const;

    void coutVCentered(std::string text) const;
    void coutVCAWCoo(short row, std::string text) const;
    void coutVerticalCenteredMultilineString(int startAtRow, std::string multilineString) const;

    void coutHelp() const;
    void coutGameOver() const;
};


