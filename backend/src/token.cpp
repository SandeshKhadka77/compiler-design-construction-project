#include "token.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Unknown:
            return "Unknown";
        case TokenType::Identifier:
            return "Identifier";
        case TokenType::IntegerLiteral:
            return "IntegerLiteral";
        case TokenType::FloatLiteral:
            return "FloatLiteral";
        case TokenType::StringLiteral:
            return "StringLiteral";
        case TokenType::Keyword:
            return "Keyword";
        case TokenType::Operator:
            return "Operator";
        case TokenType::Separator:
            return "Separator";
        case TokenType::EndOfFile:
            return "EndOfFile";
    }

    return "Unknown";
}
