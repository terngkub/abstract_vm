#pragma once
#include <string>

enum class TokenType
{
	Int8, Int16, Int32, Double, Float,
	Push, Pop, Dump, Assert,
	Add, Sub, Mul, Div, Mod,
	Print, Exit,
	Error
};

class Token
{
public:
	TokenType type;
	int line_nb;
	std::string str;

	Token(TokenType, int line_nb, std::string);
	~Token();

private:
	// unimplemented
	Token();
};
