#pragma once
#include "ioperand.hpp"
#include "factory.hpp"
#include "exception.hpp"
#include <sstream>
#include <typeinfo>
#include <variant>
#include <cmath>
#include <iostream>


template <typename T>
class Operand : public IOperand
{
using var_t = std::variant<long long, long double>;

public:
	// Constructor
	Operand() = delete;
	Operand(T value) :
		precision(0),
		type(eOperandType::Int8),
		value(value),
		str(std::to_string(value))
	{
		// TODO change this to map
		if		(typeid(T) == typeid(int8_t))	{ precision = 0;	type = eOperandType::Int8; }
		else if (typeid(T) == typeid(int16_t))	{ precision = 0;	type = eOperandType::Int16; }
		else if (typeid(T) == typeid(int32_t))	{ precision = 0;	type = eOperandType::Int32; }
		else if (typeid(T) == typeid(float))	{ precision = 7;	type = eOperandType::Float; }
		else if (typeid(T) == typeid(double))	{ precision = 15;	type = eOperandType::Double; }
		// TODO else throw
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
		return operation([](auto l, auto r)->var_t{return l + r;}, rhs);
	}

	IOperand const * operator-(IOperand const & rhs) const
	{
		return operation([](auto l, auto r)->var_t{return l - r;}, rhs);
	}

	IOperand const * operator*(IOperand const & rhs) const
	{
		return operation([](auto l, auto r)->var_t{return l * r;}, rhs);
	}

	IOperand const * operator/(IOperand const & rhs) const
	{
		if (std::stold(rhs.toString()) == 0)
			throw DivisionByZeroException{};
		return operation([](auto l, auto r)->var_t{return l / r;}, rhs);
	}

	IOperand const * operator%(IOperand const & rhs) const
	{
		if (std::stold(rhs.toString()) == 0)
			throw ModuloByZeroException{};
		auto new_type = (type > rhs.getType()) ? type : rhs.getType();
		auto result = (new_type < eOperandType::Float)
				? std::to_string(static_cast<long long>(value) % std::stoll(rhs.toString()))
				: std::to_string(fmod(static_cast<long double>(value), std::stold(rhs.toString())));
		return factory().createOperand(new_type, result);
	}

private:

	int				precision;
	eOperandType	type;
	T				value;
	std::string		str;

	template <typename OptFunc>
	IOperand const * operation(OptFunc opt, IOperand const & rhs) const
	{
		auto new_type = (type > rhs.getType()) ? type : rhs.getType();
		var_t left_val = (new_type < eOperandType::Float) ? static_cast<long long>(value) : static_cast<long double>(value);
		var_t right_val = (new_type < eOperandType::Float) ? std::stoll(rhs.toString()) : std::stold(rhs.toString());
		var_t result_val = std::visit(opt, left_val, right_val);
		auto result_str = std::visit(
				[](auto arg){ return std::to_string(arg); },
				result_val);
		return factory().createOperand(new_type, result_str);
	}
};