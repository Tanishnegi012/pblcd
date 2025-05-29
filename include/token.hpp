#pragma once
#include <string>

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    IDENTIFIER,
    EQUALS,
    SEMICOLON,
    IF,
    ELSE,
    THEN,
    END,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,
    EQUAL_EQUAL,
    NOT_EQUAL,
    END_OF_FILE,
    INVALID
};

class Token {
public:
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType type, std::string lexeme, int line, int column)
        : type(type), lexeme(std::move(lexeme)), line(line), column(column) {}

    std::string toString() const;
}; 