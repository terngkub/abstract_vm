#pragma once
#include "IOperand.hpp"
#include <list>

class OperandFactory
{
    IOperand const * (OperandFactory::*func_ptr[5])(std::string const &) const;

    /*
    OperandFactory(OperandFactory const & src);
    OperandFactory & operator=(OperandFactory const & rhs);
    */

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;


public:
    OperandFactory();
    ~OperandFactory();

	IOperand const * createOperand(eOperandType type, std::string const & value) const;
};

OperandFactory & instance();