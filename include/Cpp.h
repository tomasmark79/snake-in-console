//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <string>
#include <sstream>

class Cpp
{
    std::string cppV;
public:
    Cpp();
    const std::string getCppV() const;
    friend std::ostream& operator<<(std::ostream& str, const Cpp& cp);
};
