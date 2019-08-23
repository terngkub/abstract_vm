#include "lexer.hpp"
#include <iostream>
#include <regex>

std::array<Pattern, 2> Lexer::patterns =
{{
	{TokenType::exit, std::regex{"^exit$"}, 0},
	{TokenType::add, std::regex{"^add$"}, 0}
}};

std::string error_message(int line_nb, std::string err)
{
	std::stringstream ss;
	ss << "line " << line_nb << " : " << err;
	return ss.str();
}

Lexer::Lexer(std::istream & is) :
	is(is)
{}

Lexer::~Lexer() {}

Token Lexer::match(int line_nb, std::string line)
{
	for (auto & pattern : patterns)
	{
		std::smatch matches;
		if (std::regex_search(line, matches, pattern.pat))
			return Token{pattern.type, matches[pattern.index]};
	}
	return Token{TokenType::error, error_message(line_nb, "not match")};
}

std::list<Token> Lexer::scan()
{
	std::list<Token> token_list;
	int line_nb = 0;

	for (std::string line; getline(is, line); )
	{
		auto token = match(++line_nb, line);
		token_list.push_back(token);
	}
	return token_list;
}