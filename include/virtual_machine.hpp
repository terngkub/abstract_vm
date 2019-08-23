#pragma once
#include <stack>
#include "ioperand.hpp"

class VirtualMachine
{
    std::istream & is;
    std::stack<IOperand *> stack;

    VirtualMachine();

public:
    VirtualMachine(std::istream & is);
    ~VirtualMachine();
    void run();
};
