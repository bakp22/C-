#include "lexer.h"
#include <iostream>
#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

#include <unordered_map>
#include <string>

using Environment = std::unordered_map<std::string, int>;



struct ExpressionNode {
    virtual ~ExpressionNode() {}
    virtual int evaluate(Environment& env) = 0;

};

// hiearchy tree operation of a simple operation 
struct BinaryExpressionNode : ExpressionNode { 
    std::shared_ptr<ExpressionNode> left; //pointer to left value  //left operand 
    Token op; //operator
    std::shared_ptr<ExpressionNode> right; //right operand

    //constructor for BinaryExpressionNode 
    BinaryExpressionNode(std::shared_ptr<ExpressionNode> left_, Token op_, std::shared_ptr<ExpressionNode> right_)
        : left(std::move(left_)), op(op_), right(std::move(right_)) {}

    int evaluate(Environment& env) override {
        int leftside = left -> evaluate(env);
        int rightside = right -> evaluate(env);

        char oper = op.value[0];


        switch(oper){
            case '+': return leftside + rightside;
            case '-': return leftside - rightside;
            case '*': return leftside * rightside;
            case '/': 
                if (rightside == 0) throw std::runtime_error("Division by zero");
                return leftside / rightside;
            default:
                throw std::runtime_error("Unknown operator");
        }
    }


    /* 
        a+b
        x+y
    */
};

// represents literal values like 42, "hello", true
struct LiteralExpressionNode : ExpressionNode {
    Token name;

    //constructor
    LiteralExpressionNode(Token name)
        : name(name) {}

    int evaluate(Environment&) override{
        return std::stoi(name.value);
    }
};

// represents variables like x, total, myFunc
struct VariableExpressionNode : ExpressionNode {
    Token name;

    //constructor
    VariableExpressionNode(Token name)
        : name(name) {}  
    
    int evaluate(Environment& env) override {
        if (env.find(name.value) == env.end()) {
            throw std::runtime_error("Undefined variable: " + name.value);
        }
        return env[name.value];
    }
};

// for expressions in parentheses like (a + b)
struct GroupingExpressionNode : ExpressionNode {
    std::shared_ptr<ExpressionNode> expression;
    
    //constructor
    GroupingExpressionNode(std::shared_ptr<ExpressionNode> expression)
        : expression(expression) {}
    
    int evaluate(Environment& env) override {
        return expression->evaluate(env);
    }
};

struct AssignExpressionNode : ExpressionNode {
    Token name;
    std::shared_ptr<ExpressionNode> value; //general pointer to any node of ExpressionNode type

    AssignExpressionNode(Token name, std::shared_ptr<ExpressionNode> value)
        : name(name), value(value) {}
    
    int evaluate(Environment& env) override {
        int val = value->evaluate(env);
        env[name.value] = val;
        return val;
    }
};

struct CallExpressionNode : ExpressionNode {
    Token name;
    std::shared_ptr<ExpressionNode> whatsCalled;
    std::vector<std::shared_ptr<ExpressionNode>> parameters;

    CallExpressionNode(Token name, std::shared_ptr<ExpressionNode> whatsCalled, std::vector<std::shared_ptr<ExpressionNode>> parameters)
        : name(name), whatsCalled(whatsCalled), parameters(parameters) {}
};

struct FunctionNode : ExpressionNode {
    Token returnType;
    Token name;  // function name token
    std::vector<Token> parameters; // parameter tokens
    std::shared_ptr<ExpressionNode> body;  // function body expression or block

    FunctionNode(Token returnType, Token name, std::vector<Token> params, std::shared_ptr<ExpressionNode> body)
        : returnType(returnType), name(name), parameters(params), body(body) {}
};


//Parser functions and helper functions 

