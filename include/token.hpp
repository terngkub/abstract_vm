#pragma once
#include <string>

enum class TokenType
{
	add,
	exit, error
};

class Token
{
	Token();

public:
	TokenType type;
	std::string str;

	Token(TokenType, std::string);
	~Token();
};
