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
    Cpp()
        : cppV{}
    {
        if (__cplusplus == 202101L) this->cppV = "C++23";
        else if (__cplusplus == 202002L) this->cppV ="C++20";
        else if (__cplusplus == 201703L) this->cppV = "C++17";
        else if (__cplusplus == 201402L) this->cppV = "C++14";
        else if (__cplusplus == 201103L) this->cppV = "C++11";
        else if (__cplusplus == 199711L) this->cppV = "C++98";
        else this->cppV = "pre-standard C++." + __cplusplus;
    }

    std::string getCppV() const
    {
        return this->cppV;
    };

    friend std::ostream& operator<<(std::ostream& str, const Cpp& cp)
    {
        return str << cp.cppV;
    };
};
