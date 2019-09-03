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
		// TODO change this to map
		switch(inst.type)
		{
			case TokenType::Push:	push(std::move(inst.operand)); break;
			case TokenType::Pop:	pop(); break;
			case TokenType::Dump:	dump(); break;
			case TokenType::Assert:	assert(std::move(inst.operand)); break;
			case TokenType::Add:	binary_operation(inst); break;
			case TokenType::Sub:	binary_operation(inst); break;
			case TokenType::Mul:	binary_operation(inst); break;
			case TokenType::Div:	binary_operation(inst); break;
			case TokenType::Mod:	binary_operation(inst); break;
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

void VirtualMachine::binary_operation(Instruction & inst)
{
	std::unordered_map<TokenType, IOperand const * (*)(OperandPtr &&, OperandPtr &&)> binary_func
	{
		{TokenType::Add, [](auto && left, auto && right){ return *left + *right; }},
		{TokenType::Sub, [](auto && left, auto && right){ return *left - *right; }},
		{TokenType::Mul, [](auto && left, auto && right){ return *left * *right; }},
		{TokenType::Div, [](auto && left, auto && right){ return *left / *right; }},
		{TokenType::Mod, [](auto && left, auto && right){ return *left % *right; }}
	};
	auto right = pop_stack();
	auto left = pop_stack();
	stack.push_front(OperandPtr(binary_func[inst.type](std::move(left), std::move(right))));
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
