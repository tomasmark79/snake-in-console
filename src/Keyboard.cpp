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
        case 'w':
            // up
            return 0;
        case 'W':
            // up
            return 0;
        case 's':
            // down
            return 1;
        case 'S':
            // down
            return 1;
        case 'a':
            // left
            return 2;
        case 'A':
            // left
            return 2;
        case 'd':
            // right
            return 3;
        case 'D':
            // right
            return 3;
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
