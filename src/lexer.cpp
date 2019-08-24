#include "lexer.hpp"
#include <iostream>

void Lexer::match()
{
	if (current_line.size() == 0) return;
	if (current_line[0] == ';') return;
	if (match_plain()) return;
	if (match_value()) return;
	token_list.push_back(Token{TokenType::Error, line_nb, "not match"});
}

bool Lexer::match_plain()
{
	if (plain_inst_map.find(current_line) != plain_inst_map.end())
	{
		token_list.push_back(Token{plain_inst_map[current_line], line_nb, current_line});
		return true;
	}
	return false;
}

bool Lexer::match_value()
{
	std::smatch matches;
	if (std::regex_search(current_line, matches, value_inst_pattern))
	{
		auto inst_type = (matches.str(1) == "push") ? TokenType::Push : TokenType::Assert;
		token_list.push_back(Token{inst_type, line_nb, matches.str(1)});

		if (matches.str(2).compare(0, 3, "int") == 0 && matches.str(3).find('.') != std::string::npos)
		{
			token_list.push_back(Token{TokenType::Error, line_nb, "integer type contain decimal point"});
		}
		else
		{
			TokenType value_type;
			if		(matches.str(2) == "int8")	value_type = TokenType::Int8;
			else if	(matches.str(2) == "int16")	value_type = TokenType::Int16;
			else if	(matches.str(2) == "int32")	value_type = TokenType::Int32;
			else if	(matches.str(2) == "float")	value_type = TokenType::Float;
			else								value_type = TokenType::Double;
			token_list.push_back(Token{value_type, line_nb, matches.str(3)});
		}
		return true;
	}
	return false;
}

Lexer::Lexer(std::istream & is) :
	plain_inst_map{
		{"pop",		TokenType::Pop},
		{"dump",	TokenType::Dump},
		{"add",		TokenType::Add},
		{"sub",		TokenType::Sub},
		{"mul",		TokenType::Mul},
		{"div",		TokenType::Div},
		{"mod",		TokenType::Mod},
		{"print",	TokenType::Print},
		{"exit",	TokenType::Exit}
	},
	value_inst_pattern{R"((push|assert) (int(?:8|16|32)|float|double)\((\-?[[:digit:]]+(?:\.[[:digit:]]+)?)\))"},
	is(is)
{}

Lexer::~Lexer() {}

std::list<Token> Lexer::scan()
{
	while (getline(is, current_line))
	{
		if (typeid(is) == typeid(std::cin) && current_line == ";;")
			break;
		match();
	}
	return token_list;
}