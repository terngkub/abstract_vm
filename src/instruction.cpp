#include "instruction.hpp"

Instruction::Instruction(TokenType type) :
    type(type),
    operand(nullptr)
{}

Instruction::Instruction(TokenType type, OperandPtr && operand) :
    type(type),
    operand(std::move(operand))
{}
