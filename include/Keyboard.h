#pragma once
#include <windows.h>
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType);
class Keyboard
{
    public:
        Keyboard();
        int getMyKeyboardCode() const;
};
