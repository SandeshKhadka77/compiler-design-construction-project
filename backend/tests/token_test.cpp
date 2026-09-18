#include "token.h"

#include <cassert>

int main() {
    const Token token{TokenType::Identifier, "total", 3, 5};

    assert(token.type == TokenType::Identifier);
    assert(token.lexeme == "total");
    assert(token.line == 3);
    assert(token.column == 5);
    assert(tokenTypeToString(TokenType::IntegerLiteral) == "IntegerLiteral");
    assert(tokenTypeToString(TokenType::EndOfFile) == "EndOfFile");

    return 0;
}
