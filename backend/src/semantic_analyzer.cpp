#include "semantic_analyzer.h"

#include <sstream>

namespace {
std::string declarationName(const std::string& declaration) {
    const std::size_t separator = declaration.find(' ');
    return separator == std::string::npos ? "" : declaration.substr(separator + 1);
}

std::string declarationType(const std::string& declaration) {
    const std::size_t separator = declaration.find(' ');
    return separator == std::string::npos ? "" : declaration.substr(0, separator);
}

bool isNumeric(ValueType type) {
    return type == ValueType::Int || type == ValueType::Float;
}
}

void SemanticAnalyzer::analyze(const AstNode& program) {
    symbolTable = SymbolTable();
    semanticErrors.clear();
    analyzeNode(program);
}

const std::vector<SemanticError>& SemanticAnalyzer::errors() const {
    return semanticErrors;
}

const SymbolTable& SemanticAnalyzer::symbols() const {
    return symbolTable;
}

ValueType SemanticAnalyzer::analyzeNode(const AstNode& node) {
    switch (node.type) {
        case AstNodeType::Program:
        case AstNodeType::IfStatement:
        case AstNodeType::WhileStatement:
            for (const auto& child : node.children) {
                analyzeNode(*child);
            }
            return ValueType::Unknown;
        case AstNodeType::VariableDeclaration: {
            const std::string name = declarationName(node.value);
            const ValueType type = valueTypeFromString(declarationType(node.value));
            if (!symbolTable.define(name, type)) {
                addError("Variable '" + name + "' is already declared");
            }
            if (!node.children.empty() && analyzeExpression(*node.children[0]) != type) {
                addError("Initializer type does not match variable '" + name + "'");
            }
            return type;
        }
        case AstNodeType::Assignment: {
            const Symbol* symbol = symbolTable.lookup(node.value);
            if (!symbol) {
                addError("Variable '" + node.value + "' is not declared");
            } else if (!node.children.empty() && analyzeExpression(*node.children[0]) != symbol->type) {
                addError("Assignment type does not match variable '" + node.value + "'");
            }
            return ValueType::Unknown;
        }
        default:
            return analyzeExpression(node);
    }
}

ValueType SemanticAnalyzer::analyzeExpression(const AstNode& node) {
    if (node.type == AstNodeType::Identifier) {
        const Symbol* symbol = symbolTable.lookup(node.value);
        if (!symbol) {
            addError("Variable '" + node.value + "' is not declared");
            return ValueType::Unknown;
        }
        return symbol->type;
    }
    if (node.type == AstNodeType::Literal) {
        if (node.value.size() >= 2 && node.value.front() == '"' && node.value.back() == '"') return ValueType::String;
        for (const char character : node.value) {
            if (character == '.') return ValueType::Float;
        }
        return ValueType::Int;
    }
    if (node.type == AstNodeType::BinaryExpression) {
        const ValueType left = analyzeExpression(*node.children[0]);
        const ValueType right = analyzeExpression(*node.children[1]);
        if (node.value == "==" || node.value == "!=" || node.value == ">" || node.value == "<" ||
            node.value == ">=" || node.value == "<=") return ValueType::Bool;
        if (!isNumeric(left) || !isNumeric(right)) {
            addError("Arithmetic operators require numeric operands");
            return ValueType::Unknown;
        }
        return left == ValueType::Float || right == ValueType::Float ? ValueType::Float : ValueType::Int;
    }
    return ValueType::Unknown;
}

void SemanticAnalyzer::addError(const std::string& message) {
    semanticErrors.push_back({message});
}
