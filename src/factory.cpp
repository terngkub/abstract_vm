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
	std::stringstream ss{value};
	long long big_n;
	ss >> big_n;

	if (is_positive_overflow<long long, int8_t>(big_n))
		throw PositiveOverflowException{};
	else if (is_negative_overflow<long long, int8_t>(big_n))
		throw NegativeOverflowException{};

	int8_t small_n = static_cast<int8_t>(big_n);
	return (new Operand<int8_t>(small_n));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
	std::stringstream ss{value};
	long long big_n;
	ss >> big_n;

	if (is_positive_overflow<long long, int16_t>(big_n))
		throw PositiveOverflowException{};
	else if (is_negative_overflow<long long, int16_t>(big_n))
		throw NegativeOverflowException{};

	int16_t small_n = static_cast<int16_t>(big_n);
	return (new Operand<int16_t>(small_n));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
	std::stringstream ss{value};
	long long big_n;
	ss >> big_n;

	if (is_positive_overflow<long long, int32_t>(big_n))
		throw PositiveOverflowException{};
	else if (is_negative_overflow<long long, int32_t>(big_n))
		throw NegativeOverflowException{};

	int32_t small_n = static_cast<int32_t>(big_n);
	return (new Operand<int32_t>(small_n));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
	std::stringstream ss{value};
	long double big_n;
	ss >> big_n;

	if (is_positive_overflow<long double, float>(big_n))
		throw PositiveOverflowException{};
	else if (is_negative_overflow<long double, float>(big_n))
		throw NegativeOverflowException{};
	else if (big_n > 0 && is_underflow<long double, float>(big_n))
		throw UnderflowException{};

	float small_n = static_cast<float>(big_n);
	return (new Operand<float>(small_n));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
	std::stringstream ss{value};
	long double big_n;
	ss >> big_n;

	if (is_positive_overflow<long double, double>(big_n))
		throw PositiveOverflowException{};
	else if (is_negative_overflow<long double, double>(big_n))
		throw NegativeOverflowException{};
	else if (big_n > 0 && is_underflow<long double, double>(big_n))
		throw UnderflowException{};

	double small_n = static_cast<double>(big_n);
	return (new Operand<double>(small_n));
}
