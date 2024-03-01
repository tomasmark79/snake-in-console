#ifndef COMPILER_H
#define COMPILER_H
#include <string>
class Compiler
{
    std::string compilerVersion;
    public:
        Compiler();
        const std::string getCompilerVersionDescription() const;
};

#endif // COMPILER_H
