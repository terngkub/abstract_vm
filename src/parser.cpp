#include "exception.hpp"
#include "parser.hpp"
#include "factory.hpp"
#include <sstream>

Parser::Parser(std::list<Token> token_list) :
	token_list(token_list),
	error_list{}
{}

Parser::~Parser() {}

std::list<Instruction> Parser::parse()
{
	std::list<Instruction> inst_list;
	for (auto it = token_list.begin(); it != token_list.end(); ++it)
	{
		if (it->type == TokenType::Error)
		{
			error_list.push_back({it->line_nb, it->str});
		}
		else if (it->type == TokenType::Push || it->type == TokenType::Assert)
		{
			auto & tmp = *it;
			++it;
			IOperand const * operand;
			try
			{
				switch(it->type)
				{
					case TokenType::Int8:	operand = factory().createOperand(eOperandType::Int8, it->str); break;
					case TokenType::Int16:	operand = factory().createOperand(eOperandType::Int16, it->str); break;
					case TokenType::Int32:	operand = factory().createOperand(eOperandType::Int32, it->str); break;
					case TokenType::Float:	operand = factory().createOperand(eOperandType::Float, it->str); break;
					case TokenType::Double:	operand = factory().createOperand(eOperandType::Double, it->str); break;
					default: throw AvmException(it->str);
				}
				inst_list.push_back(Instruction{tmp.type, operand});
			}
			catch(AvmException const & e)
			{
				error_list.push_back({it->line_nb, e.what()});
			}
		}
		else
		{
			inst_list.push_back(Instruction{it->type});
		}
	}
	// TODO check if contain exit
	if (!error_list.empty())
	{
		std::stringstream ss;
		ss << "Error: there is at least one error in the input\n";
		for (auto & err : error_list)
		{
			ss << "Line " << err.first << ": " << err.second << std::endl;
		}
		throw AvmException(ss.str());
	}
	return inst_list;
}