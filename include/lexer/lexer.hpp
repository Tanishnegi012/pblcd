#pragma once
#include <string>
#include <vector>
#include "../token.hpp"

class Lexer {
public:
    explicit Lexer(std::string source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t start = 0;
    size_t current = 0;
    int line = 1;
    int column = 1;

    char advance();
    char peek() const;
    char peekNext() const;
    bool isAtEnd() const;
    void skipWhitespace();
    
    Token number();
    Token identifier();
    Token makeToken(TokenType type);
    bool match(char expected);
}; 