#pragma once
#include "token.hpp"
#include "ioperand.hpp"

class Instruction
{
public:
	// TODO getter with const
	TokenType type;
	int line_nb;
	OperandPtr operand;

	// Constructor
	Instruction() = delete;
	Instruction(TokenType type, int line_nb);
	Instruction(TokenType type, int line_nb, OperandPtr && operand);

	// Destructor
	~Instruction() = default;

	// Copy - disable
	Instruction(Instruction const &) = delete;
	Instruction & operator=(Instruction const &) = delete;

	// Move - enable
	Instruction(Instruction &&) = default;
	Instruction & operator=(Instruction &&) = default;
};