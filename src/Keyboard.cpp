//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Keyboard.h"
#include "conio.h" // _kbhit && _getch


Keyboard::Keyboard()
{
    if (!SetConsoleCtrlHandler(CtrlHandler, true))
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

        case UP3:
            return 30;
        case DOWN3:
            return 31;
        case LEFT3:
            return 32;
        case RIGHT3:
            return 33;

        case UP4:
            return 40;
        case DOWN4:
            return 41;
        case LEFT4:
            return 42;
        case RIGHT4:
            return 43;


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
            return 6;
        case 'R':
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
