#include "factory.hpp"
#include "operand.hpp"
#include "exception.hpp"
#include <iostream>

// Public

Factory::Factory() :
	func_ptr
	{
		&Factory::createInt8,
		&Factory::createInt16,
		&Factory::createInt32,
		&Factory::createFloat,
		&Factory::createDouble
	}
{}

Factory::~Factory()
{
}

OperandPtr Factory::createOperandPtr(eOperandType type, std::string const & value) const
{
	return OperandPtr(createOperand(type, value));
}

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const
{
	return (this->*func_ptr[type])(value);
}

Factory & factory()
{
	static Factory instance;
	return instance;
}

// Private

IOperand const *Factory::createInt8(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int8_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int8_t>(big_n))
		throw AvmException("Underflow on a value");

	int8_t small_n = static_cast<int8_t>(big_n);
	return (new Operand<int8_t>(small_n));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int16_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int16_t>(big_n))
		throw AvmException("Underflow on a value");

	int16_t small_n = static_cast<int16_t>(big_n);
	return (new Operand<int16_t>(small_n));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
	long long big_n = std::stoll(value);

	if (is_overflow<long long, int32_t>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long long, int32_t>(big_n))
		throw AvmException("Underflow on a value");

	int32_t small_n = static_cast<int32_t>(big_n);
	return (new Operand<int32_t>(small_n));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
	long double big_n = std::stold(value);

	if (is_overflow<long double, float>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long double, float>(big_n))
		throw AvmException("Underflow on a value");

	float small_n = static_cast<float>(big_n);
	return (new Operand<float>(small_n));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
	long double big_n = std::stold(value);

	if (is_overflow<long double, double>(big_n))
		throw AvmException("Overflow on a value");
	else if (is_underflow<long double, double>(big_n))
		throw AvmException("Underflow on a value");

	double small_n = static_cast<double>(big_n);
	return (new Operand<double>(small_n));
}
