#ifndef MINI_COMPILER_AST_H
#define MINI_COMPILER_AST_H

#include <memory>
#include <string>
#include <vector>

enum class AstNodeType {
    Program,
    VariableDeclaration,
    Assignment,
    IfStatement,
    WhileStatement,
    BinaryExpression,
    Identifier,
    Literal
};

std::string astNodeTypeToString(AstNodeType type);

struct AstNode {
    AstNodeType type;
    std::string value;
    std::vector<std::unique_ptr<AstNode>> children;

    AstNode(AstNodeType type, const std::string& value = "");

    void addChild(std::unique_ptr<AstNode> child);
};

std::unique_ptr<AstNode> makeAstNode(AstNodeType type, const std::string& value = "");

#endif
