#pragma once
#include "token.hpp"
#include "ioperand.hpp"

class Instruction
{
public:
    // TODO getter with const
    TokenType type;
    IOperand const * operand;

    Instruction(TokenType type);
    Instruction(TokenType type, IOperand const * operand);
    ~Instruction();

private:
    Instruction();
};