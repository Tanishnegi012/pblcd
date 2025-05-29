#pragma once
#include <string>

class Optimizer {
public:
    std::string optimize(const std::string& ir) {
        // For now, we'll just return the IR as is
        return ir;
    }
}; 