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
#include <windows.h>
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);
class Keyboard
{
    enum playerControlLayout1
    {
        UP1 = 'w',
        DOWN1 = 's',
        LEFT1 = 'a',
        RIGHT1 = 'd'
    };

    enum playerControlLayout2
    {
        UP2 = 'i',
        DOWN2 = 'k',
        LEFT2 = 'j',
        RIGHT2 = 'l'
    };

    enum playerControlLayout3
    {
        UP3 = '8',
        DOWN3 = '5',
        LEFT3 = '4',
        RIGHT3 = '6'
    };

    enum playerControlLayout4
    {
        UP4 = '[',
        DOWN4 = '\'',
        LEFT4 = ';',
        RIGHT4 = '\\'
    };

public:
    Keyboard();
    int getMyKeyboardCode() const;
};
