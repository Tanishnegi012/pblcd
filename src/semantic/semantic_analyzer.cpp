#include "../../include/semantic/semantic_analyzer.hpp"
#include <stdexcept>

SemanticAnalyzer::SemanticAnalyzer() {}

void SemanticAnalyzer::analyze(std::shared_ptr<ASTNode> ast) {
    if (auto binary = std::dynamic_pointer_cast<BinaryExpr>(ast)) {
        visitBinaryExpr(binary);
    } else if (auto number = std::dynamic_pointer_cast<NumberExpr>(ast)) {
        visitNumberExpr(number);
    }
}

void SemanticAnalyzer::visitBinaryExpr(std::shared_ptr<BinaryExpr> expr) {
    analyze(expr->left);
    analyze(expr->right);
    
    // For now, we only support numeric operations
    // In a more complex language, we would check type compatibility here
    if (expr->op.type != TokenType::PLUS && 
        expr->op.type != TokenType::MINUS && 
        expr->op.type != TokenType::MULTIPLY && 
        expr->op.type != TokenType::DIVIDE) {
        throw std::runtime_error("Invalid operator for numeric operation");
    }
}

void SemanticAnalyzer::visitNumberExpr(std::shared_ptr<NumberExpr> expr) {
    // Verify that the number is valid
    try {
        std::stod(expr->value.lexeme);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid number: " + expr->value.lexeme);
    }
}

void SemanticAnalyzer::checkTypes(const std::string& left, const std::string& right, const Token& op) {
    // In this simple implementation, we only have numbers
    // In a more complex language, this would check type compatibility
    if (left != "number" || right != "number") {
        throw std::runtime_error("Type mismatch: both operands must be numbers");
    }
} 