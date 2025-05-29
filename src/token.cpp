#include "../include/token.hpp"

std::string Token::toString() const {
    std::string typeStr;
    switch (type) {
        case TokenType::NUMBER: typeStr = "NUMBER"; break;
        case TokenType::PLUS: typeStr = "PLUS"; break;
        case TokenType::MINUS: typeStr = "MINUS"; break;
        case TokenType::MULTIPLY: typeStr = "MULTIPLY"; break;
        case TokenType::DIVIDE: typeStr = "DIVIDE"; break;
        case TokenType::LPAREN: typeStr = "LPAREN"; break;
        case TokenType::RPAREN: typeStr = "RPAREN"; break;
        case TokenType::IDENTIFIER: typeStr = "IDENTIFIER"; break;
        case TokenType::EQUALS: typeStr = "EQUALS"; break;
        case TokenType::SEMICOLON: typeStr = "SEMICOLON"; break;
        case TokenType::END_OF_FILE: typeStr = "EOF"; break;
        case TokenType::INVALID: typeStr = "INVALID"; break;
    }
    return "[" + typeStr + " '" + lexeme + "' at line " + std::to_string(line) + 
           ", column " + std::to_string(column) + "]";
} 