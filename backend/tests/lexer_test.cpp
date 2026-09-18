#include "lexer.h"

#include <cassert>

int main() {
    Lexer lexer("int total = 12; // comment\nfloat rate = 2.5;");
    const std::vector<Token> tokens = lexer.tokenize();

    assert(lexer.errors().empty());
    assert(tokens.size() == 11);
    assert(tokens[0].type == TokenType::Keyword);
    assert(tokens[0].lexeme == "int");
    assert(tokens[1].type == TokenType::Identifier);
    assert(tokens[3].type == TokenType::IntegerLiteral);
    assert(tokens[5].type == TokenType::Keyword);
    assert(tokens[10].type == TokenType::EndOfFile);

    Lexer operators("value >= 10 && other != 0;");
    const std::vector<Token> operatorTokens = operators.tokenize();
    assert(operatorTokens[1].type == TokenType::Operator);
    assert(operatorTokens[1].lexeme == ">=");
    assert(!operators.errors().empty());

    Lexer invalid("int value = 1.2.3;");
    invalid.tokenize();
    assert(invalid.errors().size() == 1);

    Lexer unterminated("string message = \"hello");
    unterminated.tokenize();
    assert(unterminated.errors().size() == 1);

    return 0;
}
