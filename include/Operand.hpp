#pragma once
#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand
{


public:

	int getPrecision()
    {

    }

	eOperandType getType()
    {
        
    }

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

	~IOperand() {}

};