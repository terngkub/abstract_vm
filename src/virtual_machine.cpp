#include "virtual_machine.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

VirtualMachine::VirtualMachine(std::istream & is) :
	is(is)
{}

VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run()
{
	Lexer lexer{is};
	auto token_list = lexer.scan();
	std::cout << "Test lexer\n";
	for (auto & token : token_list)
		std::cout << token.str << std::endl;

	Parser parser{token_list};
	auto inst_list = parser.parse();

	for (auto & inst : inst_list)
	{
		(void)inst;
	}
}
