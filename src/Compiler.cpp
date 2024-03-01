#include "Compiler.h"

Compiler::Compiler()
{
    if (__cplusplus == 202101L) this->compilerVersion = "C++23";
    else if (__cplusplus == 202002L) this->compilerVersion ="C++20";
    else if (__cplusplus == 201703L) this->compilerVersion = "C++17";
    else if (__cplusplus == 201402L) this->compilerVersion = "C++14";
    else if (__cplusplus == 201103L) this->compilerVersion = "C++11";
    else if (__cplusplus == 199711L) this->compilerVersion = "C++98";
    else this->compilerVersion = "pre-standard C++." + __cplusplus;
}

const std::string Compiler::getCompilerVersionDescription() const
{
    return this->compilerVersion;
}
