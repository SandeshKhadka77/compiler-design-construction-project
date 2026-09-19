#include "ir_generator.h"
#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"

#include <cassert>

int main() {
    Lexer lexer("int total = 2 + 3; total = total * 4;");
    const std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    std::unique_ptr<AstNode> program = parser.parse();

    SemanticAnalyzer analyzer;
    analyzer.analyze(*program);
    assert(lexer.errors().empty());
    assert(parser.errors().empty());
    assert(analyzer.errors().empty());
    assert(analyzer.symbols().contains("total"));

    IrGenerator generator;
    const std::vector<std::string> instructions = generator.generate(*program);
    assert(instructions.size() == 4);
    assert(instructions[0].find("t1 = 2 + 3") != std::string::npos);
    assert(instructions[1].find("total = t1") != std::string::npos);
    assert(instructions[3].find("total = t2") != std::string::npos);

    Lexer invalidLexer("int count = 1; result = count + 2;");
    Parser invalidParser(invalidLexer.tokenize());
    std::unique_ptr<AstNode> invalidProgram = invalidParser.parse();
    SemanticAnalyzer invalidAnalyzer;
    invalidAnalyzer.analyze(*invalidProgram);
    assert(!invalidAnalyzer.errors().empty());

    return 0;
}
