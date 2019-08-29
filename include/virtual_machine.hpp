#pragma once
#include <list>
#include "ioperand.hpp"
#include "instruction.hpp"

class VirtualMachine
{
public:
    VirtualMachine(std::istream & is);
    ~VirtualMachine();
    void run();

private:
    std::istream & is;
    std::list<IOperand const *> stack;

    IOperand const * pop_stack();
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

    // unimplemented
    VirtualMachine();
};
