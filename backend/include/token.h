#ifndef MINI_COMPILER_TOKEN_H
#define MINI_COMPILER_TOKEN_H

#include <string>

enum class TokenType {
    Unknown,
    Identifier,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    Keyword,
    Operator,
    Separator,
    EndOfFile
};

std::string tokenTypeToString(TokenType type);

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

#endif
