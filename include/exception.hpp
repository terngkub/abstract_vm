#pragma once
#include <exception>
#include <string>

class ParsingException : public std::exception {};
class RuntimeException : public std::exception {};

class FloatingIntegerException : public ParsingException
{ public: virtual const char * what() const noexcept; };

class PositiveOverflowException : public ParsingException, public RuntimeException
{ public: virtual const char * what() const noexcept; };

class NegativeOverflowException : public ParsingException, public RuntimeException
{ public: virtual const char * what() const noexcept; };

class UnderflowException : public ParsingException, public RuntimeException
{ public: virtual const char * what() const noexcept; };

class EmptyStackException : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class DivisionByZeroException : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class ModuloByZeroException : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class FalseAssertionException : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class StackLessThanTwoException : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class NotInt8Exception : public RuntimeException
{ public: virtual const char * what() const noexcept; };

class FloatingBitwiseException : public RuntimeException
{ public: virtual const char * what() const noexcept; };
