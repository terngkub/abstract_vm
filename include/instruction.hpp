#pragma once
#include "token.hpp"
#include "ioperand.hpp"

class Instruction
{
    Instruction();

public:
    TokenType type;
    IOperand const * operand;

    Instruction(TokenType type);
    Instruction(TokenType type, IOperand const * operand);
    ~Instruction();
};