#pragma once
#include "token.hpp"
#include "instruction.hpp"
#include <list>

class Parser
{
public:
    Parser(std::list<Token> token_list);
    ~Parser();
    std::list<Instruction> parse();

private:
    std::list<Token> token_list;
    std::list<std::pair<int, std::string>> error_list;

    Parser();
};