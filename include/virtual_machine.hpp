#pragma once
#include <list>
#include "ioperand.hpp"
#include "instruction.hpp"

class VirtualMachine
{
public:
    // Constructor
    VirtualMachine() = delete;
    VirtualMachine(std::istream & is);

    // Destructor
    ~VirtualMachine() = default;

    // Copy - disable
    VirtualMachine(VirtualMachine const &) = delete;
    VirtualMachine & operator=(VirtualMachine const &) = delete;

    // Move - disable
    VirtualMachine(VirtualMachine &&) = delete;
    VirtualMachine & operator=(VirtualMachine &&) = delete;

    // Public Methods
    void run();

private:
    std::istream & is;
    std::list<OperandPtr> stack;

    OperandPtr pop_stack();
    void do_inst(Instruction & inst);
    void push(OperandPtr && operand);
    void pop();
    void dump() const;
    void assert(OperandPtr && operand) const;
    void print() const;

    void binary_operation(Instruction & inst);
};
