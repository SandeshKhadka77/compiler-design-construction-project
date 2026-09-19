#include "ir_generator.h"

namespace {
std::string declarationName(const std::string& declaration) {
    const std::size_t separator = declaration.find(' ');
    return separator == std::string::npos ? declaration : declaration.substr(separator + 1);
}
}

std::vector<std::string> IrGenerator::generate(const AstNode& program) {
    instructions.clear();
    temporaryCount = 0;
    labelCount = 0;
    for (const auto& child : program.children) {
        generateStatement(*child);
    }
    return instructions;
}

std::string IrGenerator::generateExpression(const AstNode& node) {
    if (node.type == AstNodeType::Identifier || node.type == AstNodeType::Literal) return node.value;
    if (node.type != AstNodeType::BinaryExpression) return "";

    const std::string result = nextTemporary();
    instructions.push_back(result + " = " + generateExpression(*node.children[0]) + " " + node.value + " " +
                           generateExpression(*node.children[1]));
    return result;
}

void IrGenerator::generateStatement(const AstNode& node) {
    if (node.type == AstNodeType::VariableDeclaration) {
        if (!node.children.empty()) {
            instructions.push_back(declarationName(node.value) + " = " + generateExpression(*node.children[0]));
        }
        return;
    }
    if (node.type == AstNodeType::Assignment) {
        instructions.push_back(node.value + " = " + generateExpression(*node.children[0]));
        return;
    }
    if (node.type == AstNodeType::IfStatement || node.type == AstNodeType::WhileStatement) {
        const std::string endLabel = nextLabel();
        instructions.push_back("ifFalse " + generateExpression(*node.children[0]) + " goto " + endLabel);
        for (std::size_t index = 1; index < node.children.size(); ++index) generateStatement(*node.children[index]);
        instructions.push_back(endLabel + ":");
    }
}

std::string IrGenerator::nextTemporary() {
    return "t" + std::to_string(++temporaryCount);
}

std::string IrGenerator::nextLabel() {
    return "L" + std::to_string(++labelCount);
}
