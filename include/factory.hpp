#pragma once
#include "ioperand.hpp"
#include <list>
#include <limits>

class Factory
{
public:
	// Constructor
    Factory();

	// Destructor
    ~Factory() = default;

	// Copy - disable
	Factory(Factory const &) = delete;
	Factory & operator=(Factory const &) = delete;

	// Move - disable
	Factory(Factory &&) = delete;
	Factory & operator=(Factory &&) = delete;

	// Public Methods
	IOperand const * createOperand(eOperandType type, std::string const & value) const;

private:
    IOperand const * (Factory::*func_ptr[5])(std::string const &) const;
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	template <typename Big, typename Small>
	bool is_overflow(Big value) const
	{
		if (value > std::numeric_limits<Small>::max())
			return true;
		return false;
	}

	template <typename Big, typename Small>
	bool is_underflow(Big value) const
	{
		if (value < std::numeric_limits<Small>::lowest())
			return true;
		return false;
	}
};

Factory & factory();
