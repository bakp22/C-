#include <iostream>

#include "parser.h"


int main() {
    tokens = {
        Token(TokenType::Identifier, "x", 1, 1),
        Token(TokenType::Assign, "=", 1, 2),
        Token(TokenType::Number, "3", 1, 3),
        Token(TokenType::Operator, "+", 1, 4),
        Token(TokenType::Number, "5", 1, 5),
    };

    current = 0;
    Environment env;

    try {
        auto assignment = parseAssignment();
        int result = assignment->evaluate(env);
        std::cout << "x = " << env["x"] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
