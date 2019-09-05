#include "exception.hpp"
#include "parser.hpp"
#include "factory.hpp"
#include <iostream>
#include <unordered_map>

Parser::Parser(std::list<Token> token_list) :
	token_list(token_list),
	inst_list{},
	error_list{},
	has_exit{false}
{}

std::list<Instruction> Parser::parse()
{
	parse_loop();
	check_error();
	return std::move(inst_list);
}

void Parser::parse_loop()
{
	for (auto it = token_list.begin(); it != token_list.end(); ++it)
	{
		if (it->type == TokenType::Error)
		{
			error_list.push_back({it->line_nb, it->str});
		}
		else if (it->type == TokenType::Push || it->type == TokenType::Assert)
			parse_inst_with_operand(it);
		else
		{
			if (it->type == TokenType::Exit)
				has_exit = true;
			inst_list.push_back(Instruction(it->type, it->line_nb));
		}
	}
}

void Parser::parse_inst_with_operand(std::list<Token>::iterator & it)
{
	try
	{
		auto & tmp = *it++;
		if (it->type == TokenType::Error)
			throw FloatingIntegerException{};
		static const std::unordered_map<TokenType, eOperandType> type_map
		{
			{TokenType::Int8, eOperandType::Int8},
			{TokenType::Int16, eOperandType::Int16},
			{TokenType::Int32, eOperandType::Int32},
			{TokenType::Float, eOperandType::Float},
			{TokenType::Double, eOperandType::Double}
		};
		IOperand const * operand = factory().createOperand(type_map.at(it->type), it->str);
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
		std::cerr << "The assembly program includes one or several lexical errors or syntactic errors.\n";
		for (auto & err : error_list)
			std::cerr << "Line " << err.first << ": " << err.second << std::endl;
		if (!has_exit)
			std::cerr << "The program doesn't have an exit instruction\n";
		throw ParsingException{};
	}
}