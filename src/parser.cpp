#include "parser.hpp"

Parser::Parser(std::list<Token> token_list) :
    token_list(token_list),
    error_list{}
{}

Parser::~Parser() {}

std::list<Instruction> Parser::parse()
{
    std::list<Instruction> inst_list;
    for (auto & token : token_list)
    {
        (void)token;
    }
    return inst_list;
}