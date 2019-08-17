#include "OperandFactory.hpp"
#include "Operand.hpp"
#include <iostream>

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	std::stringstream s{value};
	int16_t big_n = 0;
	s >> big_n;
	int8_t small_n = static_cast<int8_t>(big_n);
	return (new Operand<int8_t>(small_n));
}

IOperand const *OperandFactory::createInt16(std::string const &value) const
{
	std::stringstream s{value};
	int16_t n;
	s >> n;
	return (new Operand<int16_t>(n));
}

IOperand const *OperandFactory::createInt32(std::string const &value) const
{
	std::stringstream s{value};
	int32_t n;
	s >> n;
	return (new Operand<int32_t>(n));
}

IOperand const *OperandFactory::createFloat(std::string const &value) const
{
	std::stringstream s{value};
	float n;
	s >> n;
	return (new Operand<int8_t>(n));
}

IOperand const *OperandFactory::createDouble(std::string const &value) const
{
	std::stringstream s{value};
	double n;
	s >> n;
	return (new Operand<int8_t>(n));
}

OperandFactory::OperandFactory() :
	func_ptr
	{
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	}
{}

OperandFactory::~OperandFactory()
{
}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	return (this->*func_ptr[type])(value);
}

OperandFactory & instance()
{
	static OperandFactory instance;
	return instance;
}
