#include "operand_type.hpp"
#include <unordered_map>
#include <iostream>

std::ostream & operator<<(std::ostream & os, eOperandType const & e)
{
    static const std::unordered_map<eOperandType, std::string> enum_str_map
    {
        {eOperandType::Int8, "int8"},
        {eOperandType::Int16, "int16"},
        {eOperandType::Int32, "int32"},
        {eOperandType::Float, "float"},
        {eOperandType::Double, "double"}
    };
    os << enum_str_map.at(e);
    return os;
}
