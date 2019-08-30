#pragma once
#include "token.hpp"
#include "ioperand.hpp"

class Instruction
{
public:
	// TODO getter with const
	TokenType type;
	OperandPtr operand;

	Instruction(TokenType type);
	Instruction(TokenType type, OperandPtr && operand);
	~Instruction();
	Instruction(Instruction &&) = default;
	Instruction & operator=(Instruction &&) = default;


	//Instruction(Instruction const && rhs) { std::swap(this, rhs); }

private:
/*
	Instruction();
	Instruction(Instruction const &);
	*/
};