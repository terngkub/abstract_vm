#include "OperandFactory.hpp"
#include "Operand.hpp"
#include <iostream>

int main()
{
    auto factory = instance();
    auto a = factory.createOperand(Int8, "123");
    std::cout << a->toString() << std::endl;
}