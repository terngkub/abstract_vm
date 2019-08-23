#include "instruction.hpp"

Instruction::Instruction(TokenType type) :
    type(type),
    operand(nullptr)
{}

Instruction::Instruction(TokenType type, IOperand * operand) :
    type(type),
    operand(operand)
{}

Instruction::~Instruction() {}