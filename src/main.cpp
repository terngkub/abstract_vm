#include "factory.hpp"
#include "operand.hpp"
#include <iostream>

int main()
{
    auto a = factory().createOperand(Int8, "30");
    std::cout << "a: " << a->toString() << std::endl;

    auto b = factory().createOperand(Float, "456");
    std::cout << "b: " << b->toString() << std::endl;

    auto result = *a + *b;
    std::cout << "result: " << result->toString() << std::endl;
}