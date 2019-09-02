#pragma once
#include "token.hpp"
#include "ioperand.hpp"

class Instruction
{
public:
	// TODO getter with const
	TokenType type;
	OperandPtr operand;

	// Constructor
	Instruction() = delete;
	Instruction(TokenType type);
	Instruction(TokenType type, OperandPtr && operand);

	// Destructor
	~Instruction() = default;

	// Copy - disable
	Instruction(Instruction const &) = delete;
	Instruction & operator=(Instruction const &) = delete;

	// Move - enable
	Instruction(Instruction &&) = default;
	Instruction & operator=(Instruction &&) = default;
};