#include "virtual_machine.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
	if (argc > 2)
	{
		std::cerr << "Error: wrong number of arguments\nUsage: ./avm [file]\n";
		return 1;
	}
	if (argc == 1)
	{
		VirtualMachine vm{std::cin};
		vm.run();
	}
	else
	{
		std::ifstream ifs;
		ifs.open(argv[1]);
		if (ifs.fail())
		{
			std::cerr << "Error: unable to open file " << argv[1] << std::endl;
			return 1;
		}
		VirtualMachine vm{ifs};
		vm.run();
		ifs.close();
	}
}
