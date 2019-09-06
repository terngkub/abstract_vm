#include "exception.hpp"

const char * FloatingIntegerException::what() const noexcept { return "decimal point in integer value"; }
const char * PositiveOverflowException::what() const noexcept { return "positive overflow on a value"; }
const char * NegativeOverflowException::what() const noexcept { return "negative overflow on a value"; }
const char * UnderflowException::what() const noexcept { return "underflow on a value"; }
const char * EmptyStackException::what() const noexcept { return "stack is empty"; }
const char * DivisionByZeroException::what() const noexcept { return "division by zero"; }
const char * ModuloByZeroException::what() const noexcept { return "modulo by zero"; }
const char * FalseAssertionException::what() const noexcept { return "an assert instruction is not true"; }
const char * StackLessThanTwoException::what() const noexcept { return "the stack is composed of strictly less than two values when an arithmetic instruction is executed"; }
const char * NotInt8Exception::what() const noexcept { return "operand type is not Int8"; }
const char * FloatingBitwiseException::what() const noexcept { return "bitwise operation on floating point number"; }
