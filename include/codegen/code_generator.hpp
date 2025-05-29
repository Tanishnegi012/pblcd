#pragma once
#include <string>
#include <memory>
#include "../ast.hpp"

class CodeGenerator {
public:
    std::string generate(std::shared_ptr<ASTNode> ast);
    std::string generateAssembly(const std::string& ir) { return ir; }

private:
    std::string visitNumberExpr(std::shared_ptr<NumberExpr> expr);
    std::string visitBinaryExpr(std::shared_ptr<BinaryExpr> expr);
}; 