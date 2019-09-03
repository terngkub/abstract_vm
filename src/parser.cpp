#include "exception.hpp"
#include "parser.hpp"
#include "factory.hpp"
#include <iostream>
#include <unordered_map>

Parser::Parser(std::list<Token> token_list) :
	token_list(token_list),
	error_list{},
	has_exit{false}
{}

std::list<Instruction> Parser::parse()
{
	std::list<Instruction> inst_list;
	parse_loop(inst_list);
	check_error();
	return inst_list;
}

void Parser::parse_loop(std::list<Instruction> & inst_list)
{
	for (auto it = token_list.begin(); it != token_list.end(); ++it)
	{
		if (it->type == TokenType::Error)
			error_list.push_back({it->line_nb, it->str});
		else if (it->type == TokenType::Push || it->type == TokenType::Assert)
			parse_inst_with_operand(inst_list, it);
		else
		{
			if (it->type == TokenType::Exit)
				has_exit = true;
			inst_list.push_back(Instruction(it->type, it->line_nb));
		}
	}
}

void Parser::parse_inst_with_operand(std::list<Instruction> & inst_list, std::list<Token>::iterator & it)
{
	try
	{
		auto & tmp = *it;
		++it;
		static std::unordered_map<TokenType, eOperandType> type_map
		{
			{TokenType::Int8, eOperandType::Int8},
			{TokenType::Int16, eOperandType::Int16},
			{TokenType::Int32, eOperandType::Int32},
			{TokenType::Float, eOperandType::Float},
			{TokenType::Double, eOperandType::Double}
		};
		IOperand const * operand = factory().createOperand(type_map[it->type], it->str);
		inst_list.push_back(Instruction(tmp.type, it->line_nb, OperandPtr(operand)));
	}
	catch(ParsingException const & e)
	{
		error_list.push_back({it->line_nb, e.what()});
	}
}

void Parser::check_error()
{
	if (!error_list.empty() || !has_exit)
	{
		std::cerr << "Parsing Errors:\n";
		for (auto & err : error_list)
			std::cerr << "Line " << err.first << ": " << err.second << std::endl;
		if (!has_exit)
			std::cerr << "The program doesn't have an exit instruction\n";
		throw ParsingException{};
	}
}