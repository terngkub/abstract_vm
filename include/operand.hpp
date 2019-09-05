#pragma once
#include "ioperand.hpp"
#include "factory.hpp"
#include "exception.hpp"
#include <sstream>
#include <typeinfo>
#include <cmath>
#include <iostream>


template <typename T>
class Operand : public IOperand
{
public:
	// Constructor
	Operand() = delete;
	Operand(T value) :
		precision(0),
		type(eOperandType::Int8),
		value(value)
	{
		if		(typeid(T) == typeid(int8_t))	{ precision = 0;	type = eOperandType::Int8; }
		else if (typeid(T) == typeid(int16_t))	{ precision = 0;	type = eOperandType::Int16; }
		else if (typeid(T) == typeid(int32_t))	{ precision = 0;	type = eOperandType::Int32; }
		else if (typeid(T) == typeid(float))	{ precision = 7;	type = eOperandType::Float; }
		else if (typeid(T) == typeid(double))	{ precision = 15;	type = eOperandType::Double; }
		if (type == eOperandType::Int8)
			str = std::to_string(value);
		else
		{
			std::stringstream ss;
			ss << value;
			str = ss.str();
		}
	}

	// Destructor
	~Operand() = default;

	// Copy - enable
	Operand(Operand const &) = default;
	Operand & operator=(Operand const &) = default;

	// Move - enable
	Operand(Operand &&) = default;
	Operand & operator=(Operand &&) = default;

	// Getters
	int getPrecision() const { return precision; }
	eOperandType getType() const { return type; }
	std::string const & toString() const { return str; }

	// Operator Overloads

	IOperand const * operator+(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) + std::stoll(rhs.toString()))
				: std::to_string(static_cast<long double>(value) + std::stold(rhs.toString()));
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator-(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) - std::stoll(rhs.toString()))
				: std::to_string(static_cast<long double>(value) - std::stold(rhs.toString()));
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator*(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) * std::stoll(rhs.toString()))
				: std::to_string(static_cast<long double>(value) * std::stold(rhs.toString()));
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator/(IOperand const & rhs) const
	{
		if (std::stold(rhs.toString()) == 0)
			throw DivisionByZeroException{};
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) / std::stoll(rhs.toString()))
				: std::to_string(static_cast<long double>(value) / std::stold(rhs.toString()));
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator%(IOperand const & rhs) const
	{
		if (std::stold(rhs.toString()) == 0)
			throw ModuloByZeroException{};
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) % std::stoll(rhs.toString()))
				: std::to_string(fmod(static_cast<long double>(value), std::stold(rhs.toString())));
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator&(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) & std::stoll(rhs.toString()))
				: throw FloatingBitwiseException{};
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator|(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) | std::stoll(rhs.toString()))
				: throw FloatingBitwiseException{};
		return factory().createOperand(new_type, result);
	}

	IOperand const * operator^(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) ^ std::stoll(rhs.toString()))
				: throw FloatingBitwiseException{};
		return factory().createOperand(new_type, result);
	}
	
	bool operator<(IOperand const & rhs) const
	{
		auto new_type = std::max(type, rhs.getType());
		return (new_type < eOperandType::Float)
				? static_cast<long long>(value) < std::stoll(rhs.toString())
				: static_cast<long double>(value) < std::stold(rhs.toString());
	}

private:
	int				precision;
	eOperandType	type;
	T				value;
	std::string		str;
};