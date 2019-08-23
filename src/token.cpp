#include "token.hpp"

Token::Token(TokenType type, std::string str) :
    type(type),
    str(str)
{}

Token::~Token() {}