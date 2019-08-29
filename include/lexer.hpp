#pragma once
#include "token.hpp"
#include <list>
#include <regex>
#include <unordered_map>

class Lexer
{
    std::unordered_map<std::string, TokenType> plain_inst_map;
    std::regex plain_inst_pattern;
    std::regex value_inst_pattern;
    std::istream & is;
    std::list<Token> token_list;
    std::string current_line;
    int line_nb;

    void match();
    bool match_plain();
    bool match_value();

    // unimplemented
    Lexer();
    
public:
    Lexer(std::istream & is);
    ~Lexer();
    std::list<Token> scan();
};