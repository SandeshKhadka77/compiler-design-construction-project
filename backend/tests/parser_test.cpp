#include "lexer.h"
#include "parser.h"

#include <cassert>

int main() {
    Lexer lexer("int total = 2 + 3 * 4; if (total > 5) { total = total - 1; }");
    const std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    std::unique_ptr<AstNode> program = parser.parse();

    assert(lexer.errors().empty());
    assert(parser.errors().empty());
    assert(program->type == AstNodeType::Program);
    assert(program->children.size() == 2);
    assert(program->children[0]->type == AstNodeType::VariableDeclaration);
    assert(program->children[0]->children[0]->value == "+");
    assert(program->children[0]->children[0]->children[1]->value == "*");
    assert(program->children[1]->type == AstNodeType::IfStatement);

    Lexer invalidLexer("int total = ;");
    Parser invalidParser(invalidLexer.tokenize());
    invalidParser.parse();
    assert(!invalidParser.errors().empty());

    return 0;
}
