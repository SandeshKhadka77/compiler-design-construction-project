#include "ast.h"

#include <cassert>

int main() {
    std::unique_ptr<AstNode> program = makeAstNode(AstNodeType::Program);
    std::unique_ptr<AstNode> declaration = makeAstNode(AstNodeType::VariableDeclaration, "int total");
    declaration->addChild(makeAstNode(AstNodeType::Literal, "0"));
    program->addChild(std::move(declaration));

    assert(astNodeTypeToString(AstNodeType::Program) == "Program");
    assert(astNodeTypeToString(AstNodeType::BinaryExpression) == "BinaryExpression");
    assert(program->type == AstNodeType::Program);
    assert(program->children.size() == 1);
    assert(program->children[0]->type == AstNodeType::VariableDeclaration);
    assert(program->children[0]->value == "int total");
    assert(program->children[0]->children.size() == 1);
    assert(program->children[0]->children[0]->value == "0");

    return 0;
}
