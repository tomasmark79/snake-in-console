#ifndef COMPILER_H
#define COMPILER_H
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

#endif // COMPILER_H
