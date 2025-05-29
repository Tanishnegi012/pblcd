#include "../../include/optimizer/optimizer.hpp"
#include <cctype>
Optimizer::Optimizer() {}
std::vector<IRInstruction> Optimizer::optimize(const std::vector<IRInstruction>& ir) {
    auto result = constantFolding(ir);
    result = deadCodeElimination(result);
    return result;
}

std::vector<IRInstruction> Optimizer::constantFolding(const std::vector<IRInstruction>& ir) {
    std::vector<IRInstruction> result;
    
    for (const auto& inst : ir) {
        if (inst.op != "add" && inst.op != "sub" && inst.op != "mul" && inst.op != "div") {
            result.push_back(inst);
            continue;
        }
        
        if (isConstant(inst.arg1) && isConstant(inst.arg2)) {
            int a = std::stoi(inst.arg1);
            int b = std::stoi(inst.arg2);
            int value = evaluateConstantExpr(inst.op, a, b);
            
            result.push_back({"load", std::to_string(value), "", inst.result});
        } else {
            result.push_back(inst);
        }
    }
    
    return result;
}

std::vector<IRInstruction> Optimizer::deadCodeElimination(const std::vector<IRInstruction>& ir) {
    std::vector<IRInstruction> result;
    std::unordered_map<std::string, bool> used;
    
    // First pass: mark all variables that are used as operands
    for (const auto& inst : ir) {
        if (!inst.arg1.empty() && inst.arg1[0] == 't') used[inst.arg1] = true;
        if (!inst.arg2.empty() && inst.arg2[0] == 't') used[inst.arg2] = true;
    }
    
    // Second pass: keep only instructions that define used variables or have side effects
    for (const auto& inst : ir) {
        if (used[inst.result] || inst.op == "ret") {
            result.push_back(inst);
        }
    }
    
    return result;
}

bool Optimizer::isConstant(const std::string& value) const {
    if (value.empty()) return false;
    return std::isdigit(value[0]) || (value[0] == '-' && value.length() > 1 && std::isdigit(value[1]));
}

int Optimizer::evaluateConstantExpr(const std::string& op, int a, int b) const {
    if (op == "add") return a + b;
    if (op == "sub") return a - b;
    if (op == "mul") return a * b;
    if (op == "div" && b != 0) return a / b;
    throw std::runtime_error("Invalid operation or division by zero");
} 