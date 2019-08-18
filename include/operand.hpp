#pragma once
#include "ioperand.hpp"
#include "factory.hpp"
#include <sstream>
#include <typeinfo>

template <typename T>
class Operand : public IOperand
{
	int precision;
	eOperandType type;
	T value;
	std::string str;

	Operand();
	Operand(Operand const & src) {}
	Operand & operator=(Operand const & rhs) {}

public:

	// Constructor, Destructor, Copy and Assignation

	Operand(T value) :
		precision(0),
		type(Int8),
		value(value),
		str(std::to_string(value))
	{
		if		(typeid(T) == typeid(int8_t))	{ precision = 0;	type = Int8; }
		else if (typeid(T) == typeid(int16_t))	{ precision = 0;	type = Int16; }
		else if (typeid(T) == typeid(int32_t))	{ precision = 0;	type = Int32; }
		else if (typeid(T) == typeid(float))	{ precision = 7;	type = Float; }
		else if (typeid(T) == typeid(double))	{ precision = 15;	type = Double; }
		// TODO else throw
	}

	~Operand() {}

	// Getter

	int getPrecision() const { return precision; }
	eOperandType getType() const { return type; }

	// Opeartion

	IOperand const * operator+(IOperand const & rhs) const
	{
		auto new_type = (type > rhs.getType()) ? type : rhs.getType();
		auto r_str = rhs.toString();
		auto r_value = (new_type < Float) ? std::stoll(r_str) : std::stold(r_str);
		auto result = std::to_string(value + r_value); 
		return factory().createOperand(new_type, result);
	}

	/*
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
		return str;
	}
};