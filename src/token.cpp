#include "token.hpp"

Token::Token(TokenType type, int line_nb, std::string str) :
    type(type),
    line_nb(line_nb),
    str(str)
{}
