#pragma once
#include <memory>
#include <string>
#include "token.hpp"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

class NumberExpr : public ASTNode {
public:
    double value;
    explicit NumberExpr(double value) : value(value) {}
    std::string toString() const override {
        return std::to_string(value);
    }
};

class BinaryExpr : public ASTNode {
public:
    std::shared_ptr<ASTNode> left;
    TokenType op;
    std::shared_ptr<ASTNode> right;

    BinaryExpr(std::shared_ptr<ASTNode> left, TokenType op, std::shared_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::string toString() const override {
        std::string opStr;
        switch (op) {
            case TokenType::PLUS: opStr = "+"; break;
            case TokenType::MINUS: opStr = "-"; break;
            case TokenType::MULTIPLY: opStr = "*"; break;
            case TokenType::DIVIDE: opStr = "/"; break;
            default: opStr = "?"; break;
        }
        return "(" + left->toString() + " " + opStr + " " + right->toString() + ")";
    }
}; 