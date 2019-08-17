#pragma once
#include "IOperand.hpp"
#include <sstream>
#include <typeinfo>

template <typename T>
class Operand : public IOperand
{
	int precision;
	eOperandType type;
	T value;

	Operand();
	Operand(Operand const & src) {}
	Operand & operator=(Operand const & rhs) {}

public:

	// Constructor, Destructor, Copy and Assignation

	Operand(T value) :
		value(value)
	{
		if		(typeid(T) == typeid(int8_t))	{ precision = 0;	type = Int8; }
		else if (typeid(T) == typeid(int16_t))	{ precision = 0;	type = Int16; }
		else if (typeid(T) == typeid(int32_t))	{ precision = 0;	type = Int32; }
		else if (typeid(T) == typeid(float))	{ precision = 7;	type = Float; }
		else if (typeid(T) == typeid(double))	{ precision = 14;	type = Double; }
	}

	~Operand() {}

	// Getter

	int getPrecision() const { return precision; }
	eOperandType getType() const { return type; }

	// Opeartion

	/*
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
	*/

	std::string const & toString() const
	{
		return *(new std::string(std::to_string(value)));
	}
};