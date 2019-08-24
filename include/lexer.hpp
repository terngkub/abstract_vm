#pragma once
#include "token.hpp"
#include <list>
#include <regex>

class Lexer
{
    std::map<std::string, TokenType> plain_inst_map;
    std::regex value_inst_pattern;
    std::istream & is;
    std::list<Token> token_list;
    std::string current_line;
    int line_nb;

    void match();
    bool match_unary();
    bool match_binary();

    // unimplemented
    Lexer();
    
public:
    Lexer(std::istream & is);
    ~Lexer();
    std::list<Token> scan();
};