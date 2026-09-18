#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {}

std::unique_ptr<AstNode> Parser::parse() {
    syntaxErrors.clear();
    current = 0;
    std::unique_ptr<AstNode> program = makeAstNode(AstNodeType::Program);

    while (!isAtEnd()) {
        std::unique_ptr<AstNode> node = statement();
        if (node) {
            program->addChild(std::move(node));
        }
    }

    return program;
}

const std::vector<SyntaxError>& Parser::errors() const {
    return syntaxErrors;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EndOfFile;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) {
        ++current;
    }
    return previous();
}

bool Parser::check(TokenType type, const std::string& lexeme) const {
    return peek().type == type && (lexeme.empty() || peek().lexeme == lexeme);
}

bool Parser::match(TokenType type, const std::string& lexeme) {
    if (!check(type, lexeme)) {
        return false;
    }
    advance();
    return true;
}

const Token& Parser::consume(TokenType type, const std::string& message, const std::string& lexeme) {
    if (check(type, lexeme)) {
        return advance();
    }
    addError(message, peek());
    return peek();
}

void Parser::addError(const std::string& message, const Token& token) {
    syntaxErrors.push_back({message, token.line, token.column});
    if (!isAtEnd()) {
        advance();
    }
}

std::unique_ptr<AstNode> Parser::statement() {
    if (check(TokenType::Keyword, "int") || check(TokenType::Keyword, "float") ||
        check(TokenType::Keyword, "string") || check(TokenType::Keyword, "bool")) {
        return declaration();
    }
    if (check(TokenType::Keyword, "if")) {
        return controlStatement(AstNodeType::IfStatement);
    }
    if (check(TokenType::Keyword, "while")) {
        return controlStatement(AstNodeType::WhileStatement);
    }
    if (check(TokenType::Identifier)) {
        return assignment();
    }

    addError("Expected a statement", peek());
    return nullptr;
}

std::unique_ptr<AstNode> Parser::declaration() {
    const std::string type = advance().lexeme;
    const Token& name = consume(TokenType::Identifier, "Expected a variable name");
    std::unique_ptr<AstNode> node = makeAstNode(AstNodeType::VariableDeclaration, type + " " + name.lexeme);
    if (match(TokenType::Operator, "=")) {
        node->addChild(expression());
    }
    consume(TokenType::Separator, "Expected ';' after declaration", ";");
    return node;
}

std::unique_ptr<AstNode> Parser::assignment() {
    const std::string name = advance().lexeme;
    consume(TokenType::Operator, "Expected '=' in assignment", "=");
    std::unique_ptr<AstNode> node = makeAstNode(AstNodeType::Assignment, name);
    node->addChild(expression());
    consume(TokenType::Separator, "Expected ';' after assignment", ";");
    return node;
}

std::unique_ptr<AstNode> Parser::controlStatement(AstNodeType type) {
    advance();
    consume(TokenType::Separator, "Expected '(' after control keyword", "(");
    std::unique_ptr<AstNode> node = makeAstNode(type);
    node->addChild(expression());
    consume(TokenType::Separator, "Expected ')' after condition", ")");
    consume(TokenType::Separator, "Expected '{' before block", "{");
    while (!isAtEnd() && !check(TokenType::Separator, "}")) {
        node->addChild(statement());
    }
    consume(TokenType::Separator, "Expected '}' after block", "}");
    return node;
}

std::unique_ptr<AstNode> Parser::expression() {
    return equality();
}

std::unique_ptr<AstNode> Parser::equality() {
    std::unique_ptr<AstNode> node = comparison();
    while (check(TokenType::Operator, "==") || check(TokenType::Operator, "!=")) {
        const std::string operation = advance().lexeme;
        std::unique_ptr<AstNode> binary = makeAstNode(AstNodeType::BinaryExpression, operation);
        binary->addChild(std::move(node));
        binary->addChild(comparison());
        node = std::move(binary);
    }
    return node;
}

std::unique_ptr<AstNode> Parser::comparison() {
    std::unique_ptr<AstNode> node = term();
    while (check(TokenType::Operator, ">") || check(TokenType::Operator, "<") ||
           check(TokenType::Operator, ">=") || check(TokenType::Operator, "<=")) {
        const std::string operation = advance().lexeme;
        std::unique_ptr<AstNode> binary = makeAstNode(AstNodeType::BinaryExpression, operation);
        binary->addChild(std::move(node));
        binary->addChild(term());
        node = std::move(binary);
    }
    return node;
}

std::unique_ptr<AstNode> Parser::term() {
    std::unique_ptr<AstNode> node = factor();
    while (check(TokenType::Operator, "+") || check(TokenType::Operator, "-")) {
        const std::string operation = advance().lexeme;
        std::unique_ptr<AstNode> binary = makeAstNode(AstNodeType::BinaryExpression, operation);
        binary->addChild(std::move(node));
        binary->addChild(factor());
        node = std::move(binary);
    }
    return node;
}

std::unique_ptr<AstNode> Parser::factor() {
    std::unique_ptr<AstNode> node = primary();
    while (check(TokenType::Operator, "*") || check(TokenType::Operator, "/")) {
        const std::string operation = advance().lexeme;
        std::unique_ptr<AstNode> binary = makeAstNode(AstNodeType::BinaryExpression, operation);
        binary->addChild(std::move(node));
        binary->addChild(primary());
        node = std::move(binary);
    }
    return node;
}

std::unique_ptr<AstNode> Parser::primary() {
    if (match(TokenType::IntegerLiteral) || match(TokenType::FloatLiteral) ||
        match(TokenType::StringLiteral)) {
        return makeAstNode(AstNodeType::Literal, previous().lexeme);
    }
    if (match(TokenType::Identifier)) {
        return makeAstNode(AstNodeType::Identifier, previous().lexeme);
    }
    if (match(TokenType::Separator, "(")) {
        std::unique_ptr<AstNode> node = expression();
        consume(TokenType::Separator, "Expected ')' after expression", ")");
        return node;
    }

    addError("Expected an expression", peek());
    return makeAstNode(AstNodeType::Literal, "");
}
