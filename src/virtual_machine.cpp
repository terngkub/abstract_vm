#include "virtual_machine.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "exception.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>

// Public

VirtualMachine::VirtualMachine(bool is_verbose, std::istream & is) :
	is_verbose{is_verbose},
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
	try
	{
		static const std::unordered_map<TokenType, void (VirtualMachine::*)(Instruction &)> inst_func
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
			{TokenType::And,	&VirtualMachine::binary_operation},
			{TokenType::Or,		&VirtualMachine::binary_operation},
			{TokenType::Xor,	&VirtualMachine::binary_operation},
			{TokenType::Print,	&VirtualMachine::print},
			{TokenType::Max,	&VirtualMachine::max},
			{TokenType::Min,	&VirtualMachine::min},
		};
		(this->*inst_func.at(inst.type))(inst);
	}
	catch (RuntimeException const & e)
	{
		std::cerr << "Runtime error at line " << inst.line_nb << " : " << e.what() << std::endl;
		throw RuntimeException{};
	}
}

OperandPtr VirtualMachine::pop_stack()
{
	if (stack.empty())
		throw EmptyStackException{};
	auto operand = std::move(stack.front());

	if (is_verbose)
		std::cout << "Popped " << operand->getType() << "(" << operand->toString() << ")\n";

	stack.pop_front();
	return operand;
}

void VirtualMachine::push(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : push " << inst.operand->getType() << "(" << inst.operand->toString() << ")\n";

	stack.push_front(std::move(inst.operand));
}

void VirtualMachine::pop(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : pop\n";

	if (stack.empty())
		throw EmptyStackException{};
	pop_stack();
}

void VirtualMachine::dump(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : dump\n";

	for(auto const & elem : stack)
		std::cout << elem->toString() << "\n";
}

void VirtualMachine::assert(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : assert " << inst.operand->getType() << "(" <<inst.operand->toString() << ")\n";

	auto const & top = stack.front();
	if (top->getType() != inst.operand->getType()
			|| top->toString() != inst.operand->toString())
		throw FalseAssertionException{};

	if (is_verbose)
		std::cout << "Assertion result is true\n";
}

void VirtualMachine::binary_operation(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : " << inst.type << "\n";

	if (stack.size() < 2)
		throw StackLessThanTwoException{};
	auto right = pop_stack();
	auto left = pop_stack();

	if (is_verbose)
		std::cout << left->toString() << " " << inst.type << " " << right->toString() << "\n";

	static const std::unordered_map<TokenType, IOperand const * (*)(OperandPtr &&, OperandPtr &&)> binary_func
	{
		{TokenType::Add, [](auto && left, auto && right){ return *left + *right; }},
		{TokenType::Sub, [](auto && left, auto && right){ return *left - *right; }},
		{TokenType::Mul, [](auto && left, auto && right){ return *left * *right; }},
		{TokenType::Div, [](auto && left, auto && right){ return *left / *right; }},
		{TokenType::Mod, [](auto && left, auto && right){ return *left % *right; }},
		{TokenType::And, [](auto && left, auto && right){ return *left & *right; }},
		{TokenType::Or, [](auto && left, auto && right){ return *left | *right; }},
		{TokenType::Xor, [](auto && left, auto && right){ return *left ^ *right; }}
	};
	auto opt = OperandPtr(binary_func.at(inst.type)(std::move(left), std::move(right)));

	if (is_verbose)
		std::cout << "Pushed " << opt->getType() << "(" << opt->toString() << ")\n";

	stack.push_front(std::move(opt));
}

void VirtualMachine::print(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : print\n";
	auto const & top = stack.front();
	if (top->getType() != eOperandType::Int8)
		throw NotInt8Exception{};
	std::stringstream ss{top->toString()};
	int c;
	ss >> c;
	std::cout << static_cast<char>(c);
}

bool unique_ptr_morethan(OperandPtr const & a, OperandPtr const & b)
{
	return *a < *b;
}

void VirtualMachine::max(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : max\n";
	if (stack.empty())
		throw EmptyStackException{};
	auto const & ptr = *std::max_element(stack.begin(), stack.end(), unique_ptr_morethan);
	std::cout << ptr->toString() << std::endl;
}

void VirtualMachine::min(Instruction & inst)
{
	if (is_verbose)
		std::cout << "Executing line " << inst.line_nb << " : min\n";
	if (stack.empty())
		throw EmptyStackException{};
	auto const & ptr = *std::min_element(stack.begin(), stack.end(), unique_ptr_morethan);
	std::cout << ptr->toString() << std::endl;
}
