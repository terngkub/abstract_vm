#include "exception.hpp"

AvmException::AvmException(std::string str) : str(str) {}

AvmException::~AvmException() {}

const char * AvmException::what() const noexcept
{
	return str.c_str();
}