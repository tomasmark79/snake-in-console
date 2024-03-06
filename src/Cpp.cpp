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

#include "Cpp.h"

Cpp::Cpp()
{
    if (__cplusplus == 202101L) this->cppV = "C++23";
    else if (__cplusplus == 202002L) this->cppV ="C++20";
    else if (__cplusplus == 201703L) this->cppV = "C++17";
    else if (__cplusplus == 201402L) this->cppV = "C++14";
    else if (__cplusplus == 201103L) this->cppV = "C++11";
    else if (__cplusplus == 199711L) this->cppV = "C++98";
    else this->cppV = "pre-standard C++." + __cplusplus;
}

const std::string Cpp::getCppV() const
{
    return this->cppV;
}

std::ostream& operator<<(std::ostream& str, const Cpp& cp)
{
    return str << cp.cppV;
}
