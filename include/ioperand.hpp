#pragma once
#include <string>

enum eOperandType
{
	Int8 = 0,
	Int16 = 1,
	Int32 = 2,
	Float = 3,
	Double = 4
};

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
	virtual std::string const & toString() const = 0;
	virtual ~IOperand() {}
};