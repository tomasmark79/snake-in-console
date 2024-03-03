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
        Process gameSnake(WIDTH, HEIGHT);
        return 0;
    }
    return 0;
}


