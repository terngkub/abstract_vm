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

// Private

void VirtualMachine::do_inst(Instruction & inst)
{
	static std::unordered_map<TokenType, void (VirtualMachine::*)(Instruction &)> inst_func
	{
		{TokenType::Push,	&VirtualMachine::push},
		{TokenType::Pop,	&VirtualMachine::pop},
		{TokenType::Dump,	&VirtualMachine::dump},
		{TokenType::Assert,	&VirtualMachine::assert},
		{TokenType::Add,	&VirtualMachine::binary_operation},
		{TokenType::Sub,	&VirtualMachine::binary_operation},
		{TokenType::Mul,	&VirtualMachine::binary_operation},
		{TokenType::Div,	&VirtualMachine::binary_operation},
		{TokenType::Mod,	&VirtualMachine::binary_operation},
		{TokenType::Print,	&VirtualMachine::print},
	};
	(this->*inst_func[inst.type])(inst);
}

OperandPtr VirtualMachine::pop_stack(Instruction & inst)
{
	(void)inst;
	if (stack.empty())
		throw EmptyStackException{};
	auto operand = std::move(stack.front());
	stack.pop_front();
	return operand;
}

void VirtualMachine::push(Instruction & inst)
{
	stack.push_front(std::move(inst.operand));
}

void VirtualMachine::pop(Instruction & inst)
{
	(void)inst;
	if (stack.empty())
		throw EmptyStackException{};
	stack.pop_front();
}

void VirtualMachine::dump(Instruction & inst)
{
	(void)inst;
	for(auto const & elem : stack)
		std::cout << elem->toString() << "\n";
}

void VirtualMachine::assert(Instruction & inst)
{
	auto const & top = stack.front();
	if (top->getType() != inst.operand->getType()
			|| top->toString() != inst.operand->toString())
		throw FalseAssertionException{};
}

void VirtualMachine::binary_operation(Instruction & inst)
{
	if (stack.size() < 2)
		throw StackLessThanTwoException{};
	auto right = pop_stack(inst);
	auto left = pop_stack(inst);

	static std::unordered_map<TokenType, IOperand const * (*)(OperandPtr &&, OperandPtr &&)> binary_func
	{
		{TokenType::Add, [](auto && left, auto && right){ return *left + *right; }},
		{TokenType::Sub, [](auto && left, auto && right){ return *left - *right; }},
		{TokenType::Mul, [](auto && left, auto && right){ return *left * *right; }},
		{TokenType::Div, [](auto && left, auto && right){ return *left / *right; }},
		{TokenType::Mod, [](auto && left, auto && right){ return *left % *right; }}
	};
	stack.push_front(OperandPtr(binary_func[inst.type](std::move(left), std::move(right))));
}

void VirtualMachine::print(Instruction & inst)
{
	(void)inst;
	auto const & top = stack.front();
	if (top->getType() != eOperandType::Int8)
		throw NotInt8Exception{};
	std::stringstream ss{top->toString()};
	int c;
	ss >> c;
	std::cout << static_cast<char>(c) << "\n";
}
