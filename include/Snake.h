#pragma once
class Snake
{
    int width, height, length, direction;
    char character;
    const double stepDivider = 1;
    static const short MAX_SNAKE_LENGTH = 256+1;
    int xArr[MAX_SNAKE_LENGTH];
    int yArr[MAX_SNAKE_LENGTH];
    int xTail[MAX_SNAKE_LENGTH];
    int yTail[MAX_SNAKE_LENGTH];
public:
    Snake(int width, int height);
    int* getSnakeX() const;
    int* getSnakeY() const;
    int getSnakeLength() const;
    int getSnakeDirection() const;
    const void setSnakeWay(int direction);
    const void addTail();
};

