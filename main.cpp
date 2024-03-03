#include "Process.h"
#include <iostream>

// 4K screen
// #define WIDTH   (int)340
// #define HEIGHT  (int)75

#define WIDTH   (int)50
#define HEIGHT  (int)20
int main()
{


    // Welcome to the Snake game

    while(true)
    {
        std::srand(std::time(0));
        Process gameSnake(WIDTH, HEIGHT);
        if (!gameSnake.isNextGameWanted())
            break;
    }
    return 0;
}


