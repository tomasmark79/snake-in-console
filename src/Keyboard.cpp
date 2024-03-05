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

#include "Keyboard.h"
#include "conio.h" // _kbhit && _getch


Keyboard::Keyboard()
{
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        // ERROR: Could not set control handler" << std::endl;
    }
}

int Keyboard::getMyKeyboardCode() const
{
    if (_kbhit())
    {
        switch(_getch())
        {
        case UP1:
            return 10;
        case DOWN1:
            return 11;
        case LEFT1:
            return 12;
        case RIGHT1:
            return 13;

        case UP2:
            return 20;
        case DOWN2:
            return 21;
        case LEFT2:
            return 22;
        case RIGHT2:
            return 23;

        case 'x':
            // exit
            return 4;
        case 'X':
            // exit
            return 4;
        case 'h':
            // help form
            return 5;
        case 'H':
            // help form
            return 5;
        case 'r':
            // help form
            return 6;
        case 'R':
            // help form
            return 6;
        }
    }
    return -1;
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        // cout << "Ctrl-C event\n\n";
        Beep(750, 300);
        return FALSE;

    // CTRL-CLOSE: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:
        Beep(600, 200);
        // cout << "Ctrl-Close event\n\n";
        return TRUE;

    // Pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
        Beep(900, 200);
        // cout << "Ctrl-Break event\n\n";
        return FALSE;

    case CTRL_LOGOFF_EVENT:
        Beep(1000, 200);
        // cout << "Ctrl-Logoff event\n\n";
        return FALSE;

    case CTRL_SHUTDOWN_EVENT:
        Beep(750, 500);
        // cout << "Ctrl-Shutdown event\n\n";
        return FALSE;

    default:
        return FALSE;
    }
}
