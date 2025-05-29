#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iomanip>
#include <limits>

std::unordered_map<std::string, double> variables;

double evaluateExpression(const std::string& expr);

void processCommand(const std::string& input) {
    try {
        // Trim whitespace from input first
        std::string trimmedInput = input;
        if (!trimmedInput.empty()) {
            trimmedInput.erase(0, trimmedInput.find_first_not_of(" \t"));
            trimmedInput.erase(trimmedInput.find_last_not_of(" \t") + 1);
        }

        // Check if it's an if statement
        if (trimmedInput.substr(0, 2) == "if") {
            size_t thenPos = trimmedInput.find(" then ");
            if (thenPos == std::string::npos) {
                throw std::runtime_error("Expected 'then' in if statement");
            }

            // Extract and trim condition
            std::string condition = trimmedInput.substr(2, thenPos - 2);
            condition.erase(0, condition.find_first_not_of(" \t"));
            condition.erase(condition.find_last_not_of(" \t") + 1);

            // Extract and trim then part
            std::string thenPart = trimmedInput.substr(thenPos + 6); // " then " is 6 characters
            thenPart.erase(0, thenPart.find_first_not_of(" \t"));
            thenPart.erase(thenPart.find_last_not_of(" \t") + 1);

            std::string elsePart;
            
            // Check for else clause
            size_t elsePos = thenPart.find(" else ");
            if (elsePos != std::string::npos) {
                elsePart = thenPart.substr(elsePos + 6); // " else " is 6 characters
                elsePart.erase(0, elsePart.find_first_not_of(" \t"));
                elsePart.erase(elsePart.find_last_not_of(" \t") + 1);
                thenPart = thenPart.substr(0, elsePos);
                thenPart.erase(thenPart.find_last_not_of(" \t") + 1);
            }
            
            // Evaluate condition
            double condResult = evaluateExpression(condition);
            
            if (condResult != 0) {
                processCommand(thenPart);
            } else if (!elsePart.empty()) {
                processCommand(elsePart);
            }
            return;
        }

        // Check for special commands
        if (trimmedInput == "help") {
            std::cout << "\nAvailable Commands:\n";
            std::cout << "1. Math expressions: 2 + 3 * 4\n";
            std::cout << "2. Variable assignment: x = 10\n";
            std::cout << "3. Print variable: print x\n";
            std::cout << "4. If statements: if x > 5 then y = 20\n";
            std::cout << "5. If-else statements: if x > 5 then y = 20 else y = 10\n";
            std::cout << "6. Show all variables: vars\n";
            std::cout << "7. Help: help\n";
            std::cout << "8. Exit: exit\n\n";
            return;
        }

        if (trimmedInput == "vars") {
            if (variables.empty()) {
                std::cout << "No variables defined yet.\n";
                return;
            }
            std::cout << "\nDefined Variables:\n";
            for (auto it = variables.begin(); it != variables.end(); ++it) {
                std::cout << it->first << " = " << std::fixed << std::setprecision(2) << it->second << "\n";
            }
            std::cout << "\n";
            return;
        }

        // Check if it's a print command
        if (trimmedInput.substr(0, 5) == "print") {
            std::string varName = trimmedInput.substr(5);
            // Trim whitespace
            varName.erase(0, varName.find_first_not_of(" \t"));
            varName.erase(varName.find_last_not_of(" \t") + 1);
            
            if (variables.find(varName) == variables.end()) {
                throw std::runtime_error("Undefined variable: " + varName);
            }
            std::cout << varName << " = " << std::fixed << std::setprecision(2) << variables[varName] << "\n";
            return;
        }

        // Check if it's a variable assignment
        size_t equalsPos = trimmedInput.find('=');
        if (equalsPos != std::string::npos && trimmedInput[equalsPos + 1] != '=') {
            std::string varName = trimmedInput.substr(0, equalsPos);
            // Trim whitespace
            varName.erase(0, varName.find_first_not_of(" \t"));
            varName.erase(varName.find_last_not_of(" \t") + 1);
            
            std::string expression = trimmedInput.substr(equalsPos + 1);
            double value = evaluateExpression(expression);
            variables[varName] = value;
            
            std::cout << varName << " = " << std::fixed << std::setprecision(2) << value << "\n";
            return;
        }

        // Otherwise, evaluate as expression
        double result = evaluateExpression(trimmedInput);
        std::cout << "Result: " << std::fixed << std::setprecision(2) << result << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

double evaluateExpression(const std::string& expr) {
    std::stack<double> numbers;
    std::stack<char> operators;
    std::string token;
    
    for (size_t i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;
        
        if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        else if (std::isdigit(expr[i]) || expr[i] == '.') {
            std::string numStr;
            bool hasDecimal = false;
            while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    if (hasDecimal) {
                        throw std::runtime_error("Invalid number format: multiple decimal points");
                    }
                    hasDecimal = true;
                }
                numStr += expr[i++];
            }
            i--;
            try {
                numbers.push(std::stod(numStr));
            } catch (const std::exception& e) {
                throw std::runtime_error("Invalid number format: " + numStr);
            }
        }
        else if (std::isalpha(expr[i])) {
            std::string varName;
            while (i < expr.length() && (std::isalnum(expr[i]) || expr[i] == '_')) {
                varName += expr[i++];
            }
            i--;
            
            if (variables.find(varName) == variables.end()) {
                throw std::runtime_error("Undefined variable: " + varName);
            }
            numbers.push(variables[varName]);
        }
        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                if (numbers.size() < 2) {
                    throw std::runtime_error("Invalid expression: insufficient operands");
                }
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                
                switch (op) {
                    case '+': numbers.push(a + b); break;
                    case '-': numbers.push(a - b); break;
                    case '*': numbers.push(a * b); break;
                    case '/': 
                        if (b == 0) throw std::runtime_error("Division by zero");
                        numbers.push(a / b); 
                        break;
                    case '<': numbers.push(a < b); break;
                    case '>': numbers.push(a > b); break;
                    case '=': numbers.push(a == b); break;
                    default:
                        throw std::runtime_error("Invalid operator: " + std::string(1, op));
                }
            }
            if (!operators.empty()) operators.pop();
            else throw std::runtime_error("Mismatched parentheses");
        }
        else {
            while (!operators.empty() && operators.top() != '(' && 
                   ((expr[i] == '+' || expr[i] == '-') || 
                    (operators.top() == '*' || operators.top() == '/'))) {
                if (numbers.size() < 2) {
                    throw std::runtime_error("Invalid expression: insufficient operands");
                }
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                
                switch (op) {
                    case '+': numbers.push(a + b); break;
                    case '-': numbers.push(a - b); break;
                    case '*': numbers.push(a * b); break;
                    case '/': 
                        if (b == 0) throw std::runtime_error("Division by zero");
                        numbers.push(a / b); 
                        break;
                    case '<': numbers.push(a < b); break;
                    case '>': numbers.push(a > b); break;
                    case '=': numbers.push(a == b); break;
                    default:
                        throw std::runtime_error("Invalid operator: " + std::string(1, op));
                }
            }
            operators.push(expr[i]);
        }
    }
    
    while (!operators.empty()) {
        if (numbers.size() < 2) {
            throw std::runtime_error("Invalid expression: insufficient operands");
        }
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        
        switch (op) {
            case '+': numbers.push(a + b); break;
            case '-': numbers.push(a - b); break;
            case '*': numbers.push(a * b); break;
            case '/': 
                if (b == 0) throw std::runtime_error("Division by zero");
                numbers.push(a / b); 
                break;
            case '<': numbers.push(a < b); break;
            case '>': numbers.push(a > b); break;
            case '=': numbers.push(a == b); break;
            default:
                throw std::runtime_error("Invalid operator: " + std::string(1, op));
        }
    }
    
    if (numbers.empty()) {
        throw std::runtime_error("Invalid expression: no result");
    }
    
    return numbers.top();
}

int main() {
    std::cout << "=== Advanced Calculator ===\n\n";
    std::cout << "Type 'help' for available commands\n";
    std::cout << "Type 'exit' to quit\n\n";

    std::string input;
    while (true) {
        try {
            std::cout << ">>> ";
            if (!std::getline(std::cin, input)) {
                if (std::cin.eof()) {
                    std::cout << "\nGoodbye!\n";
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            
            // Trim whitespace from input
            if (!input.empty()) {
                input.erase(0, input.find_first_not_of(" \t"));
                input.erase(input.find_last_not_of(" \t") + 1);
            }
            
            if (input == "exit") {
                std::cout << "Goodbye!\n";
                break;
            }
            
            if (!input.empty()) {
                processCommand(input);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
} 