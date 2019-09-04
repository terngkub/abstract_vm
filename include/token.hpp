#pragma once
#include <ostream>
#include <string>

enum class TokenType
{
	Int8, Int16, Int32, Double, Float,
	Push, Pop, Dump, Assert,
	Add, Sub, Mul, Div, Mod,
	And, Or, Xor,
	Print, Exit,
	Max, Min,
	Error
};

class Token
{
public:
	// Constructor
	Token() = delete;
	Token(TokenType, int line_nb, std::string);

	// Destructor
	~Token() = default;

	// Copy - enable
	Token(Token const &) = default;
	Token & operator=(Token const &) = default;

	// Move - enable
	Token(Token &&) = default;
	Token & operator=(Token &&) = default;

	TokenType type;
	int line_nb;
	std::string str;
};

std::ostream & operator<<(std::ostream & os, TokenType const & t);