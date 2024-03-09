//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <string>
#include "Field.h"
using std::string;
class Graphic
{
    Field* fie;
    char **videoBuffer;

public:
    Graphic(Field& field);
    ~Graphic();
    const void clearScreen() const;
    const void clearVideoBuffer() const;
    const void addWallsToVideoBuffer() const;
    const void addSnakeToVideoBuffer
    (
        const int id,
        const int* x,
        const int* y,
        int snakeLength,
        bool isDie
    );
    const void addFruitToVideoBuffer
    (
        const int* x,
        const int* y,
        int fruitElement
    );
    const void redrawVideoBuffer() const;

    const void Cout(string msg) const;

    const void coutVCentered(std::string text) const;
    const void coutVCAWCoo(short row, std::string text) const;

    const void coutHelp() const;
    const void coutGOver(int reason) const;
};


