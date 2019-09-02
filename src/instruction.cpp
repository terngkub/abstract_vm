#include "instruction.hpp"

Instruction::Instruction(TokenType type, int line_nb) :
    type(type),
    line_nb(line_nb),
    operand(nullptr)
{}

Instruction::Instruction(TokenType type, int line_nb, OperandPtr && operand) :
    type(type),
    line_nb(line_nb),
    operand(std::move(operand))
{}
