#pragma once
#include "token.hpp"
#include <list>
#include <regex>
#include <array>

struct Pattern
{
    TokenType type;
    std::regex pat;
    int index;
};

class Lexer
{
    std::istream & is;
    static std::array<Pattern, 2> patterns;

    Token match(int line_nb, std::string line);

    // unimplemented
    Lexer();
    
public:
    Lexer(std::istream & is);
    ~Lexer();
    std::list<Token> scan();
};