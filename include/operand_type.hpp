#pragma once
#include <ostream>

enum eOperandType
{
	Int8 = 0,
	Int16 = 1,
	Int32 = 2,
	Float = 3,
	Double = 4
};

std::ostream & operator<<(std::ostream & os, eOperandType const & e);