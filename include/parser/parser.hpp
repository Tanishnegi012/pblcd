#pragma once
#include <vector>
#include <memory>
#include "../token.hpp"
#include "../ast.hpp"

class Parser {

private:
    std::vector<Token> tokens;
    size_t current = 0;

    std::shared_ptr<ASTNode> expression();
    std::shared_ptr<ASTNode> term();
    std::shared_ptr<ASTNode> factor();
    
    Token peek() const;
    Token advance();
    bool isAtEnd() const;
    bool match(TokenType type);
    Token previous() const;
}; 
