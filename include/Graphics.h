#pragma once
#include <string>
#include "Field.h"
using std::string;
class Graphics
{
    Field* fie;
    char **videoBuffer;
public:
    Graphics(Field& field);
    ~Graphics();
    const void clearVideoBuffer() const;
    const void addWallsToVideoBuffer() const;
    const void addSnakeToVideoBuffer
    (
        const int* x,
        const int* y,
        int snakeLength
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


