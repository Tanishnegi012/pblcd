#include <iostream>
#include "../include/lexer/lexer.hpp"

int main() {
    // Test different expressions
    std::vector<std::string> tests = {
        "42",
        "3.14",
        "x = 10;",
        "1 + 2 * 3",
        "a + b * (c - d)"
    };

    for (const auto& test : tests) {
        std::cout << "\nTesting expression: " << test << "\n";
        std::cout << "------------------------\n";
        
        try {
            Lexer lexer(test);
            std::vector<Token> tokens = lexer.tokenize();
            
            for (const auto& token : tokens) {
                std::cout << token.toString() << "\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        
        std::cout << "------------------------\n";
    }

    return 0;
} 