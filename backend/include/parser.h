#ifndef MINI_COMPILER_PARSER_H
#define MINI_COMPILER_PARSER_H

#include "ast.h"
#include "token.h"

#include <memory>
#include <string>
#include <vector>

struct SyntaxError {
    std::string message;
    int line;
    int column;
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<AstNode> parse();
    const std::vector<SyntaxError>& errors() const;

private:
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& advance();
    bool check(TokenType type, const std::string& lexeme = "") const;
    bool match(TokenType type, const std::string& lexeme = "");
    const Token& consume(TokenType type, const std::string& message, const std::string& lexeme = "");
    void addError(const std::string& message, const Token& token);

    std::unique_ptr<AstNode> statement();
    std::unique_ptr<AstNode> declaration();
    std::unique_ptr<AstNode> assignment();
    std::unique_ptr<AstNode> controlStatement(AstNodeType type);
    std::unique_ptr<AstNode> expression();
    std::unique_ptr<AstNode> equality();
    std::unique_ptr<AstNode> comparison();
    std::unique_ptr<AstNode> term();
    std::unique_ptr<AstNode> factor();
    std::unique_ptr<AstNode> primary();

    std::vector<Token> tokens;
    std::size_t current;
    std::vector<SyntaxError> syntaxErrors;
};

#endif
