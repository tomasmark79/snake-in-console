//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

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
    const void clearScreen() const;
    const void clearVideoBuffer() const;
    const void addWallsToVideoBuffer() const;
    const void addSnakeToVideoBuffer
    (
        const int id,
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


