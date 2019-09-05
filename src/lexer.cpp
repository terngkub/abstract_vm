#include "lexer.hpp"
#include <iostream>
#include <regex>
#include <unordered_map>

// Public

Lexer::Lexer(std::istream & is) :
	is(is),
	token_list{},
	current_line{},
	line_nb(0)
{}

std::list<Token> Lexer::scan()
{
	while (getline(is, current_line))
	{
		++line_nb;
		if (typeid(is) == typeid(std::cin) && current_line == ";;")
			break;
		match();
	}
	return token_list;
}

// Private

void Lexer::match()
{
	if (current_line.size() == 0) return;
	if (current_line[0] == ';') return;
	if (match_plain()) return;
	if (match_value()) return;
	token_list.push_back(Token{TokenType::Error, line_nb, "an instruction in unknown"});
}

bool Lexer::match_plain()
{
	std::smatch matches;
	static const std::regex plain_inst_pattern{R"((pop|dump|add|sub|mul|div|mod|and|or|xor|print|exit|max|min)(?:[[:space:]]*?;.*)?)"};
	if (std::regex_search(current_line, matches, plain_inst_pattern))
	{
    	static const std::unordered_map<std::string, TokenType> plain_inst_map
		{
			{"pop",		TokenType::Pop},
			{"dump",	TokenType::Dump},
			{"add",		TokenType::Add},
			{"sub",		TokenType::Sub},
			{"mul",		TokenType::Mul},
			{"div",		TokenType::Div},
			{"mod",		TokenType::Mod},
			{"and",		TokenType::And},
			{"or",		TokenType::Or},
			{"xor",		TokenType::Xor},
			{"print",	TokenType::Print},
			{"exit",	TokenType::Exit},
			{"max",		TokenType::Max},
			{"min",		TokenType::Min}
		};
		token_list.push_back(Token{plain_inst_map.at(matches[1]), line_nb, matches[1]});
		return true;
	}
	return false;
}

bool Lexer::match_value()
{
	std::smatch matches;
	static const std::regex value_inst_pattern{R"((push|assert) (int(?:8|16|32)|float|double)\((\-?[[:digit:]]+(?:\.[[:digit:]]+)?)\)(?:[[:space:]]*?;.*)?)"};
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
			static const std::unordered_map<std::string, TokenType> type_map
			{
				{"int8", TokenType::Int8},
				{"int16", TokenType::Int16},
				{"int32", TokenType::Int32},
				{"float", TokenType::Float},
				{"double", TokenType::Double}
			};
			token_list.push_back(Token{type_map.at(matches.str(2)), line_nb, matches.str(3)});
		}
		return true;
	}
	return false;
}
