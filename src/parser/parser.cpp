
std::shared_ptr<ASTNode> Parser::term() {
    auto left = factor();

    while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
        TokenType op = previous().type;
        auto right = factor();
        left = std::make_shared<BinaryExpr>(left, op, right);
    }

    return left;
}

std::shared_ptr<ASTNode> Parser::factor() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<NumberExpr>(std::stod(previous().lexeme));
    }

    if (match(TokenType::LPAREN)) {
        auto expr = expression();
        if (!match(TokenType::RPAREN)) {
            throw std::runtime_error("Expected ')' after expression.");
        }
        return expr;
    }

    throw std::runtime_error("Expected number or '('.");
}

Token Parser::peek() const {
    if (isAtEnd()) return tokens.back(); // EOF token
    return tokens[current];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    advance();
    return true;
}

Token Parser::previous() const {
    return tokens[current - 1];
} 
