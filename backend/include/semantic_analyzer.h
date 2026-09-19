#ifndef MINI_COMPILER_SEMANTIC_ANALYZER_H
#define MINI_COMPILER_SEMANTIC_ANALYZER_H

#include "ast.h"
#include "symbol_table.h"

#include <string>
#include <vector>

struct SemanticError {
    std::string message;
};

class SemanticAnalyzer {
public:
    void analyze(const AstNode& program);
    const std::vector<SemanticError>& errors() const;
    const SymbolTable& symbols() const;

private:
    ValueType analyzeNode(const AstNode& node);
    ValueType analyzeExpression(const AstNode& node);
    void addError(const std::string& message);

    SymbolTable symbolTable;
    std::vector<SemanticError> semanticErrors;
};

#endif
