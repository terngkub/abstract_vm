#include "OperandFactory.hpp"
#include "Operand.hpp"
#include "exception.hpp"
#include <iostream>

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int8_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int8_t>(big_n))
		throw AvmException("Underflow on a value");

	int8_t small_n = static_cast<int8_t>(big_n);
	return (new Operand<int8_t>(small_n));
}

IOperand const *OperandFactory::createInt16(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int16_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int16_t>(big_n))
		throw AvmException("Underflow on a value");

	int16_t small_n = static_cast<int16_t>(big_n);
	return (new Operand<int16_t>(small_n));
}

IOperand const *OperandFactory::createInt32(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int32_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int32_t>(big_n))
		throw AvmException("Underflow on a value");

	int32_t small_n = static_cast<int32_t>(big_n);
	return (new Operand<int32_t>(small_n));
}

IOperand const *OperandFactory::createFloat(std::string const &value) const
{
	long double big_n = std::stold(value);

	if (is_overflow<long double, float>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long double, float>(big_n))
		throw AvmException("Underflow on a value");

	float small_n = static_cast<float>(big_n);
	return (new Operand<float>(small_n));
}

IOperand const *OperandFactory::createDouble(std::string const &value) const
{
	long double big_n = std::stold(value);

	if (is_overflow<long double, double>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long double, double>(big_n))
		throw AvmException("Underflow on a value");

	double small_n = static_cast<double>(big_n);
	return (new Operand<double>(small_n));
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

OperandFactory & factory()
{
	static OperandFactory instance;
	return instance;
}
