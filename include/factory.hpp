#pragma once
#include "ioperand.hpp"
#include <list>
#include <limits>

class Factory
{
public:
    Factory();
    ~Factory();

	OperandPtr createOperandPtr(eOperandType type, std::string const & value) const;
	IOperand const * createOperand(eOperandType type, std::string const & value) const;

private:
    IOperand const * (Factory::*func_ptr[5])(std::string const &) const;
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	// unimplemented
    Factory(Factory const & src);
    Factory & operator=(Factory const & rhs);
};

Factory & factory();

template <typename Big, typename Small>
bool is_overflow(Big value)
{
	if (value > std::numeric_limits<Small>::max())
		return true;
	return false;
}

template <typename Big, typename Small>
bool is_underflow(Big value)
{
	if (value < std::numeric_limits<Small>::lowest())
		return true;
	return false;
}