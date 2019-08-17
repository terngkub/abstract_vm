#pragma once
#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand
{
	int precision;
	eOperandType type;

public:

	// Constructor, Destructor, Copy and Move

	Operand() {}
	~Operand() {}
	Operand(Operand const & src) {}
	Operand & operator=(Operand const & rhs) {}

	// Getter

	int getPrecision() { return precision; }
	eOperandType getType() { return type; }

	// Opeartion

	IOperand const * operator+(IOperand const & rhs)
	{
		
	}

	IOperand const * operator-(IOperand const & rhs)
	{
		
	}

	IOperand const * operator*(IOperand const & rhs)
	{
		
	}

	IOperand const * operator/(IOperand const & rhs)
	{
		
	}

	IOperand const * operator%(IOperand const & rhs)
	{
		
	}

	std::string const & toString()
	{
		
	}
};