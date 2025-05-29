#include "../../include/lexer/lexer.hpp"
#include <cctype>
#include <stdexcept>
#include <unordered_map>

static std::unordered_map<std::string, TokenType> keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"then", TokenType::THEN},
    {"end", TokenType::END}
};

Lexer::Lexer(std::string source) : source(std::move(source)) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    
    while (!isAtEnd()) {
        start = current;
        
        char c = advance();
        switch (c) {
            case '(': tokens.push_back(makeToken(TokenType::LPAREN)); break;
            case ')': tokens.push_back(makeToken(TokenType::RPAREN)); break;
            case '+': tokens.push_back(makeToken(TokenType::PLUS)); break;
            case '-': tokens.push_back(makeToken(TokenType::MINUS)); break;
            case '*': tokens.push_back(makeToken(TokenType::MULTIPLY)); break;
            case '/': tokens.push_back(makeToken(TokenType::DIVIDE)); break;
            case ';': tokens.push_back(makeToken(TokenType::SEMICOLON)); break;
            case '=':
                if (match('=')) {
                    tokens.push_back(Token(TokenType::EQUAL_EQUAL, "==", line, column - 1));
                } else {
                    tokens.push_back(makeToken(TokenType::EQUALS));
                }
                break;
            case '<':
                if (match('=')) {
                    tokens.push_back(Token(TokenType::LESS_EQUAL, "<=", line, column - 1));
                } else {
                    tokens.push_back(makeToken(TokenType::LESS));
                }
                break;
            case '>':
                if (match('=')) {
                    tokens.push_back(Token(TokenType::GREATER_EQUAL, ">=", line, column - 1));
                } else {
                    tokens.push_back(makeToken(TokenType::GREATER));
                }
                break;
            case '!':
                if (match('=')) {
                    tokens.push_back(Token(TokenType::NOT_EQUAL, "!=", line, column - 1));
                } else {
                    throw std::runtime_error("Expected '=' after '!'");
                }
                break;
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                skipWhitespace();
                break;
            default:
                if (std::isdigit(c)) {
                    tokens.push_back(number());
                } else if (std::isalpha(c) || c == '_') {
                    tokens.push_back(identifier());
                } else {
                    throw std::runtime_error("Unexpected character at line " + 
                        std::to_string(line) + ", column " + std::to_string(column));
                }
        }
    }
    
    tokens.push_back(Token(TokenType::END_OF_FILE, "", line, column));
    return tokens;
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    char c = source[current++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                advance();
                break;
            default:
                return;
        }
    }
}

Token Lexer::number() {
    while (std::isdigit(peek())) advance();
    
    // Look for decimal point
    if (peek() == '.' && std::isdigit(peekNext())) {
        advance(); // Consume the '.'
        while (std::isdigit(peek())) advance();
    }
    
    std::string num = source.substr(start, current - start);
    return Token(TokenType::NUMBER, num, line, column - num.length());
}

Token Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();
    
    std::string text = source.substr(start, current - start);
    TokenType type = TokenType::IDENTIFIER;
    
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        type = it->second;
    }
    
    return Token(type, text, line, column - text.length());
}

Token Lexer::makeToken(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    return Token(type, lexeme, line, column - 1);
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) return false;
    current++;
    column++;
    return true;
} 