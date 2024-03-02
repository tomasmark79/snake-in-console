#pragma once
#include <string>
using std::string;
class Graphics
{
    char **buffer;
    int width;
    int height;
public:
    Graphics(int width /*columns*/, int height /*rows*/);
    ~Graphics();
    const void clearBuffer() const;
    const void addWallsToBuffer() const;
    const void addSnakeToBuffer(int* x,
                                int* y,
                                int length);
    const void redrawBuffer() const;
    const void printInfo(string msg) const;
};

