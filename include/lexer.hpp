#pragma once
#include "token.hpp"
#include <list>
#include <regex>
#include <unordered_map>

class Lexer
{
public:
    // Constructor
    Lexer() = delete;
    Lexer(std::istream & is);

    // Destructor
    ~Lexer() = default;

    // Copy - disable
    Lexer(Lexer const &) = delete;
    Lexer & operator=(Lexer const &) = delete;

    // Move - disable
    Lexer(Lexer &&) = delete;
    Lexer & operator=(Lexer &&) = delete;

    // Public Methods
    std::list<Token> scan();

private:
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
};