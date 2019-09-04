#include "token.hpp"
#include <unordered_map>

Token::Token(TokenType type, int line_nb, std::string str) :
    type(type),
    line_nb(line_nb),
    str(str)
{}

std::ostream & operator<<(std::ostream & os, TokenType const & t)
{
    static const std::unordered_map<TokenType, std::string> token_type_map
    {
        {TokenType::Int8, "int8"},
        {TokenType::Int16, "int16"},
        {TokenType::Int32, "int32"},
        {TokenType::Float, "float"},
        {TokenType::Double, "double"},
        {TokenType::Push, "push"},
        {TokenType::Pop, "pop"},
        {TokenType::Dump, "dump"},
        {TokenType::Assert, "assert"},
        {TokenType::Add, "add"},
        {TokenType::Sub, "sub"},
        {TokenType::Mul, "mul"},
        {TokenType::Div, "div"},
        {TokenType::Mod, "mod"},
        {TokenType::And, "and"},
        {TokenType::Or, "or"},
        {TokenType::Xor, "xor"},
        {TokenType::Print, "print"},
        {TokenType::Exit, "exit"},
        {TokenType::Max, "max"},
        {TokenType::Min, "min"},
        {TokenType::Error, "error"}
    };
    os << token_type_map.at(t);
    return os;
}