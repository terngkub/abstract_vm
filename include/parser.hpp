#pragma once
#include "token.hpp"
#include "instruction.hpp"
#include <list>

class Parser
{
public:
    // Constructor
    Parser() = delete;
    Parser(std::list<Token> token_list);

    // Destructor
    ~Parser() = default;

    // Copy - disable
    Parser(Parser const &) = delete;
    Parser & operator=(Parser const &) = delete;

    // Move - disable
    Parser(Parser &&) = delete;
    Parser & operator=(Parser &&) = delete;

    // Public Methods
    std::list<Instruction> parse();

private:
    std::list<Token> token_list;
    std::list<std::pair<int, std::string>> error_list;
};