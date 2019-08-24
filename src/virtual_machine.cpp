#include "virtual_machine.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "exception.hpp"
#include <iostream>

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

		// for test only
		std::cout << "Lexer result\n";
		for (auto & token : token_list)
			std::cout << token.str << std::endl;

		Parser parser{token_list};
		auto inst_list = parser.parse();
	}
	catch (AvmException const & e)
	{
		std::cerr << e.what();
		return;
	}

	/*
	for (auto & inst : inst_list)
	{
		std::cout << inst.type << std::endl;
	}
	*/
}
