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

    OperandPtr pop_stack(Instruction & inst);
    void do_inst(Instruction & inst);
    void push(Instruction & inst);
    void pop(Instruction & inst);
    void dump(Instruction & inst);
    void assert(Instruction & inst);
    void print(Instruction & inst);
    void binary_operation(Instruction & inst);
    void max(Instruction & inst);
    void min(Instruction & inst);
};
