#include "ast.h"

int current;
std::vector<Token> tokens; 

/*
* checks token type
* @param -type
*/
bool match(TokenType type) {
    if (current < tokens.size() && tokens[current].type == type) {
        current++;
        return true;
    }
    return false;
}

//expect the current Token to be of a certain type
Token consume(TokenType expectedType, const std::string& errorMessage) {
    if (current < tokens.size() && tokens[current].type == expectedType) {
        return tokens[current++];  // advance and return token
    }
    throw std::runtime_error(errorMessage);
}
std::shared_ptr<ExpressionNode> parseExpression();
std::shared_ptr<ExpressionNode> parsePrimary();


std::shared_ptr<ExpressionNode> parsePrimary(){
    if (match(TokenType::Number)){
        return std::make_shared<LiteralExpressionNode>(tokens[current-1]);
    }
    if (match(TokenType::Identifier)){
        return std::make_shared<VariableExpressionNode>(tokens[current-1]);
    }
    if (match(TokenType::LParenthesis)) {
        auto expr = parseExpression();
        consume(TokenType::RParenthesis, "Expect ')' after expression.");
        return std::make_shared<GroupingExpressionNode>(expr);
    }

    throw std::runtime_error("Expected expression");
}

std::shared_ptr<ExpressionNode> parseExpression() {
    return parsePrimary();
}

// std::shared_ptr<ExpressionNode> parseFunction(){

//     //Expected first tokentype is FStart
//     Token returnTypeToken = consume(TokenType::DataType, "expected a return datatype");

//     consume(TokenType::FStarter,"Missing keyword: fxn");

//     Token functionName = consume(TokenType::Identifier, "Missing function name");

//     consume(TokenType::LParenthesis,"Missing: ( ");

//     std::vector<Token> parameters;

//     while (!match(TokenType::RParenthesis)) {
//         parameters.push_back(consume(TokenType::Identifier, "Expected parameter name"));
//         if (!match(TokenType::Comma)) break;
//     }

//     consume(TokenType::RParenthesis,"Missing: ) ");

//     consume(TokenType::LBrace,"Missing { to start function body");
//     auto body = parseExpression(); // auto tells compiler to automoatically deduce the type of the variable
//     consume(TokenType::RBrace,"Missing } to end function body");

//     return std::make_shared<FunctionNode>(returnTypeToken,functionName,parameters,body);
// }


std::shared_ptr<AssignExpressionNode> parseAssignment() {
    // Step 1: Consume variable name
    Token varName = consume(TokenType::Identifier, "Expected variable name");

    // Step 2: Consume '=' token
    consume(TokenType::Assign, "Expected '=' after variable name");

    // Step 3: Parse the right-hand expression (you can improve this with full expression parsing)
    auto left = parsePrimary();  // parse a literal or variable

    // Optionally parse a binary expression if operator exists
    if (match(TokenType::Operator)) {
        Token op = tokens[current - 1];
        auto right = parsePrimary();
        auto expr = std::make_shared<BinaryExpressionNode>(left, op, right);

        // Step 4: Wrap into assignment node
        return std::make_shared<AssignExpressionNode>(varName, expr);
    }

    // If no operator, just assign the primary expression
    return std::make_shared<AssignExpressionNode>(varName, left);
}

