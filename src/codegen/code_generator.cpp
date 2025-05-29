#include "../../include/codegen/code_generator.hpp"
#include <stdexcept>

std::string CodeGenerator::generate(std::shared_ptr<ASTNode> ast) {
    if (auto numExpr = std::dynamic_pointer_cast<NumberExpr>(ast)) {
        return visitNumberExpr(numExpr);
    }
    if (auto binExpr = std::dynamic_pointer_cast<BinaryExpr>(ast)) {
        return visitBinaryExpr(binExpr);
    }
    throw std::runtime_error("Unknown AST node type");
}

std::string CodeGenerator::visitNumberExpr(std::shared_ptr<NumberExpr> expr) {
    return std::to_string(expr->value);
}

std::string CodeGenerator::visitBinaryExpr(std::shared_ptr<BinaryExpr> expr) {
    std::string left = generate(expr->left);
    std::string right = generate(expr->right);
    std::string op;
    
    switch (expr->op) {
        case TokenType::PLUS: op = "+"; break;
        case TokenType::MINUS: op = "-"; break;
        case TokenType::MULTIPLY: op = "*"; break;
        case TokenType::DIVIDE: op = "/"; break;
        default: throw std::runtime_error("Unknown operator");
    }
    
    return "(" + left + " " + op + " " + right + ")";
} 