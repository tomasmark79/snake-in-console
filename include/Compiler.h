#pragma once
#include <string>
#include <sstream>

class Compiler
{
    std::string compilerVersion;
public:
    Compiler();
    const std::string getCppCompilerV() const;
    friend std::ostream& operator<<(std::ostream& str, const Compiler& cp);
};
