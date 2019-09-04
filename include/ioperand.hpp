#pragma once
#include "operand_type.hpp"
#include <string>
#include <memory>

class IOperand
{
public:
	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;
	virtual IOperand const * operator+(IOperand const & rhs) const = 0;
	virtual IOperand const * operator-(IOperand const & rhs) const = 0;
	virtual IOperand const * operator*(IOperand const & rhs) const = 0;
	virtual IOperand const * operator/(IOperand const & rhs) const = 0;
	virtual IOperand const * operator%(IOperand const & rhs) const = 0;
	virtual IOperand const * operator&(IOperand const & rhs) const = 0; // bonus
	virtual IOperand const * operator|(IOperand const & rhs) const = 0; // bonus
	virtual IOperand const * operator^(IOperand const & rhs) const = 0; // bonus
	virtual bool operator<(IOperand const & rhs) const = 0; // bonus
	virtual std::string const & toString() const = 0;
	virtual ~IOperand() {}
};

using OperandPtr = std::unique_ptr<IOperand const>;