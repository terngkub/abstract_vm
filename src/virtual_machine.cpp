#include "virtual_machine.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "exception.hpp"
#include <iostream>

// Public

VirtualMachine::VirtualMachine(std::istream & is) :
	is(is)
{}

VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run()
{
	try
	{
		Lexer lexer{is};
		auto token_list = lexer.scan();

		Parser parser{token_list};
		auto inst_list = parser.parse();

		for (auto & inst : inst_list)
		{
			if (inst.type == TokenType::Exit)
				break;
			do_inst(inst);
		}
	}
	catch (AvmException const & e)
	{
		std::cerr << e.what() << "\n";
		return;
	}
}

// Private

void VirtualMachine::do_inst(Instruction & inst)
{
	try
	{
		switch(inst.type)
		{
			case TokenType::Push:	push(std::move(inst.operand)); break;
			case TokenType::Pop:	pop(); break;
			case TokenType::Dump:	dump(); break;
			case TokenType::Assert:	assert(std::move(inst.operand)); break;
			case TokenType::Add:	add(); break;
			case TokenType::Sub:	sub(); break;
			case TokenType::Mul:	mul(); break;
			case TokenType::Div:	div(); break;
			case TokenType::Mod:	mod(); break;
			case TokenType::Print:	print(); break;
			default: throw(AvmException("invalid instruction type"));
		}
	}
	catch(AvmException const & e)
	{
		throw;
	}
}

OperandPtr VirtualMachine::pop_stack()
{
	if (stack.empty())
		throw AvmException("stack is empty");
	auto operand = std::move(stack.front());
	stack.pop_front();
	return operand;
}

void VirtualMachine::push(OperandPtr && operand)
{
	stack.push_front(std::move(operand));
}

void VirtualMachine::pop()
{
	stack.pop_front();
}

void VirtualMachine::dump()
{
	for(auto & elem : stack)
	{
		std::cout << elem->toString() << "\n";
	}
}

void VirtualMachine::assert(OperandPtr && operand)
{
	auto & top = stack.front();
	if (top->getType() != operand->getType()
			|| top->toString() != operand->toString())
		throw AvmException("assert instruction is not true");
}

void VirtualMachine::add()
{
	try
	{
		auto left = pop_stack();
		auto right = pop_stack();
		stack.push_front(OperandPtr(*left + *right));
	}
	catch (AvmException const & e)
	{
		throw;
	}
}

void VirtualMachine::sub()
{
	try
	{
		auto left = pop_stack();
		auto right = pop_stack();
		stack.push_front(OperandPtr(*left - *right));
	}
	catch (AvmException const & e)
	{
		throw;
	}
}

void VirtualMachine::mul()
{
	try
	{
		auto left = pop_stack();
		auto right = pop_stack();
		stack.push_front(OperandPtr(*left * *right));
	}
	catch (AvmException const & e)
	{
		throw;
	}
}

void VirtualMachine::div()
{
	try
	{
		auto left = pop_stack();
		auto right = pop_stack();
		stack.push_front(OperandPtr(*left / *right));
	}
	catch (AvmException const & e)
	{
		throw;
	}
}

void VirtualMachine::mod()
{
	try
	{
		auto left = pop_stack();
		auto right = pop_stack();
		stack.push_front(OperandPtr(*left % *right));
	}
	catch (AvmException const & e)
	{
		throw;
	}
}

void VirtualMachine::print()
{
	try
	{
		auto & top = stack.front();
		if (top->getType() != eOperandType::Int8)
			throw AvmException("operand type is not int8");
		std::stringstream ss{top->toString()};
		int c;
		ss >> c;
		std::cout << static_cast<char>(c) << "\n";
	}
	catch(AvmException const & e)
	{
		throw;
	}
	
}
