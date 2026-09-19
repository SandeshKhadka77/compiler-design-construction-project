#ifndef MINI_COMPILER_IR_GENERATOR_H
#define MINI_COMPILER_IR_GENERATOR_H

#include "ast.h"

#include <string>
#include <vector>

class IrGenerator {
public:
    std::vector<std::string> generate(const AstNode& program);

private:
    std::string generateExpression(const AstNode& node);
    void generateStatement(const AstNode& node);
    std::string nextTemporary();
    std::string nextLabel();

    std::vector<std::string> instructions;
    int temporaryCount;
    int labelCount;
};

#endif
