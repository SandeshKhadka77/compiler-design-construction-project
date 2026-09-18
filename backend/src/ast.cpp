#include "ast.h"

std::string astNodeTypeToString(AstNodeType type) {
    switch (type) {
        case AstNodeType::Program:
            return "Program";
        case AstNodeType::VariableDeclaration:
            return "VariableDeclaration";
        case AstNodeType::Assignment:
            return "Assignment";
        case AstNodeType::IfStatement:
            return "IfStatement";
        case AstNodeType::WhileStatement:
            return "WhileStatement";
        case AstNodeType::BinaryExpression:
            return "BinaryExpression";
        case AstNodeType::Identifier:
            return "Identifier";
        case AstNodeType::Literal:
            return "Literal";
    }

    return "Unknown";
}

AstNode::AstNode(AstNodeType type, const std::string& value)
    : type(type), value(value) {}

void AstNode::addChild(std::unique_ptr<AstNode> child) {
    children.push_back(std::move(child));
}

std::unique_ptr<AstNode> makeAstNode(AstNodeType type, const std::string& value) {
    return std::unique_ptr<AstNode>(new AstNode(type, value));
}
