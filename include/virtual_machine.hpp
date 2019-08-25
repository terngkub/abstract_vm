#pragma once
#include <list>
#include "ioperand.hpp"
#include "instruction.hpp"

class VirtualMachine
{
    std::istream & is;
    std::list<IOperand const *> stack;

    VirtualMachine();

    // utils
    IOperand const * pop_stack();

    // do instruction
    void do_inst(Instruction & inst);
    void push(IOperand const * operand);
    void pop();
    void dump();
    void assert(IOperand const * operand);
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
    void exit();

public:
    VirtualMachine(std::istream & is);
    ~VirtualMachine();
    void run();
};
