#pragma once
#include <string>
#include "Field.h"
using std::string;
class Graphics
{
    Field* fie;
    char **buffer;
public:
    Graphics(Field& field);
    ~Graphics();
    const void clearBuffer() const;
    const void addWallsToBuffer() const;
    const void addSnakeToBuffer(
        int* x,
        int* y,
        int length);
    const void addFruitToBuffer(
        int* x,
        int* y,
        int fruitCount);
    const void redrawBuffer() const;
    const void printInfo(string msg) const;
    const void prntVrtCenText(short row, std::string text) const;
    const void prntGameOver(int reason) const;
    const void printHelp() const;
    int getScreenWidth() const;
    int getScreenHeight() const;
};


