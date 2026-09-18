#include "lexer.h"

#include <cctype>
#include <unordered_set>

namespace {
const std::unordered_set<std::string> keywords = {
    "int", "float", "string", "bool", "if", "while"
};
}

Lexer::Lexer(const std::string& source)
    : source(source), current(0), line(1), column(1), tokenStartColumn(1) {}

std::vector<Token> Lexer::tokenize() {
    tokens.clear();
    lexicalErrors.clear();
    current = 0;
    line = 1;
    column = 1;

    while (!isAtEnd()) {
        tokenStartColumn = column;
        scanToken();
    }

    tokens.push_back({TokenType::EndOfFile, "", line, column});
    return tokens;
}

const std::vector<LexicalError>& Lexer::errors() const {
    return lexicalErrors;
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

char Lexer::advance() {
    const char character = source[current++];
    ++column;
    return character;
}

char Lexer::peek() const {
    return isAtEnd() ? '\0' : source[current];
}

void Lexer::scanToken() {
    const char character = advance();

    if (character == ' ' || character == '\r' || character == '\t') {
        return;
    }

    if (character == '\n') {
        ++line;
        column = 1;
        return;
    }

    if (std::isalpha(static_cast<unsigned char>(character)) || character == '_') {
        --current;
        --column;
        scanIdentifierOrKeyword();
        return;
    }

    if (std::isdigit(static_cast<unsigned char>(character))) {
        --current;
        --column;
        scanNumber();
        return;
    }

    if (character == '"') {
        scanString();
        return;
    }

    if (character == '/' && peek() == '/') {
        while (!isAtEnd() && peek() != '\n') {
            advance();
        }
        return;
    }

    if (character == '=' || character == '!' || character == '>' || character == '<') {
        if (peek() == '=') {
            advance();
            addToken(TokenType::Operator);
        } else if (character == '!') {
            addError("'!' must be followed by '='", line, tokenStartColumn);
        } else {
            addToken(TokenType::Operator);
        }
        return;
    }

    if (character == '+' || character == '-' || character == '*' || character == '/') {
        addToken(TokenType::Operator);
        return;
    }

    if (character == ';' || character == '(' || character == ')' || character == '{' || character == '}') {
        addToken(TokenType::Separator);
        return;
    }

    addError("Unexpected character '" + std::string(1, character) + "'", line, tokenStartColumn);
}

void Lexer::scanIdentifierOrKeyword() {
    while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') {
        advance();
    }

    const std::string lexeme = source.substr(current - (column - tokenStartColumn), column - tokenStartColumn);
    const TokenType type = keywords.count(lexeme) > 0 ? TokenType::Keyword : TokenType::Identifier;
    tokens.push_back({type, lexeme, line, tokenStartColumn});
}

void Lexer::scanNumber() {
    while (std::isdigit(static_cast<unsigned char>(peek()))) {
        advance();
    }

    TokenType type = TokenType::IntegerLiteral;
    if (peek() == '.') {
        type = TokenType::FloatLiteral;
        advance();
        if (!std::isdigit(static_cast<unsigned char>(peek()))) {
            addError("A decimal point must be followed by digits", line, column - 1);
        }
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            advance();
        }
    }

    if (peek() == '.') {
        addError("Invalid number format", line, column);
        while (std::isdigit(static_cast<unsigned char>(peek())) || peek() == '.') {
            advance();
        }
    }

    const std::string lexeme = source.substr(current - (column - tokenStartColumn), column - tokenStartColumn);
    tokens.push_back({type, lexeme, line, tokenStartColumn});
}

void Lexer::scanString() {
    while (!isAtEnd() && peek() != '"' && peek() != '\n') {
        advance();
    }

    if (isAtEnd() || peek() == '\n') {
        addError("Unterminated string literal", line, tokenStartColumn);
        return;
    }

    advance();
    const std::string lexeme = source.substr(current - (column - tokenStartColumn), column - tokenStartColumn);
    tokens.push_back({TokenType::StringLiteral, lexeme, line, tokenStartColumn});
}

void Lexer::addToken(TokenType type) {
    const std::string lexeme = source.substr(current - (column - tokenStartColumn), column - tokenStartColumn);
    tokens.push_back({type, lexeme, line, tokenStartColumn});
}

void Lexer::addError(const std::string& message, int errorLine, int errorColumn) {
    lexicalErrors.push_back({message, errorLine, errorColumn});
}
