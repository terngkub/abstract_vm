#include "virtual_machine.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "exception.hpp"
#include <iostream>

// Public

VirtualMachine::VirtualMachine(std::istream & is) :
	is(is)
{}

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
		std::cerr << e.what();
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
	catch(AvmException & e)
	{
		std::stringstream ss;
		ss << "Line " << inst.line_nb << " : " << e.what() << std::endl;
		throw AvmException(ss.str());
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
	if (stack.empty())
		throw AvmException("stack is empty");
	stack.pop_front();
}

void VirtualMachine::dump() const
{
	for(auto const & elem : stack)
	{
		std::cout << elem->toString() << "\n";
	}
}

void VirtualMachine::assert(OperandPtr && operand) const
{
	auto const & top = stack.front();
	if (top->getType() != operand->getType()
			|| top->toString() != operand->toString())
		throw AvmException("assert instruction is not true");
}

void VirtualMachine::add()
{
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(*left + *right));
}

void VirtualMachine::sub()
{
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(*left - *right));
}

void VirtualMachine::mul()
{
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(*left * *right));
}

void VirtualMachine::div()
{
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(*left / *right));
}

void VirtualMachine::mod()
{
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(*left % *right));
}

void VirtualMachine::print() const
{
	auto const & top = stack.front();
	if (top->getType() != eOperandType::Int8)
		throw AvmException("operand type is not int8");
	std::stringstream ss{top->toString()};
	int c;
	ss >> c;
	std::cout << static_cast<char>(c) << "\n";
}
