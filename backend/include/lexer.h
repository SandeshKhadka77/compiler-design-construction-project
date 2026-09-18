#ifndef MINI_COMPILER_LEXER_H
#define MINI_COMPILER_LEXER_H

#include "token.h"

#include <string>
#include <vector>

struct LexicalError {
    std::string message;
    int line;
    int column;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();
    const std::vector<LexicalError>& errors() const;

private:
    bool isAtEnd() const;
    char advance();
    char peek() const;
    void scanToken();
    void scanIdentifierOrKeyword();
    void scanNumber();
    void scanString();
    void addToken(TokenType type);
    void addError(const std::string& message, int errorLine, int errorColumn);

    std::string source;
    std::vector<Token> tokens;
    std::vector<LexicalError> lexicalErrors;
    std::size_t current;
    int line;
    int column;
    int tokenStartColumn;
};

#endif
