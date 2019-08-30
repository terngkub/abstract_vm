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
    std::list<OperandPtr> stack;

    OperandPtr pop_stack();
    void do_inst(Instruction & inst);
    void push(OperandPtr && operand);
    void pop();
    void dump();
    void assert(OperandPtr && operand);
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
