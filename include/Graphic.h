//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>
#include <string>

using std::string;
class Graphic
{
    std::shared_ptr<Field> fie; // Field* fie;
    char **videoBuffer;

public:
    Graphic(std::shared_ptr<Field> field);
    Graphic(const Graphic& other); //
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

    void Cout(string msg) const;

    void coutVCentered(std::string text) const;
    void coutVCAWCoo(short row, std::string text) const;

    void coutHelp() const;
    void coutGOver(int reason) const;
};


