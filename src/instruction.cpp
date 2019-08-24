#include "instruction.hpp"

Instruction::Instruction(TokenType type) :
    type(type),
    operand(nullptr)
{}

Instruction::Instruction(TokenType type, IOperand const * operand) :
    type(type),
    operand(operand)
{}

Instruction::~Instruction() {}