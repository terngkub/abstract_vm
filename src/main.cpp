#include "virtual_machine.hpp"
#include <iostream>
#include <fstream>

void vm_input_mode(bool is_verbose)
{
	VirtualMachine vm{is_verbose, std::cin};
	vm.run();
}

void vm_file_mode(bool is_verbose, std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.fail())
	{
		std::cerr << "Error: unable to open file " << filename << std::endl;
		throw std::exception{};
	}
	VirtualMachine vm{is_verbose, ifs};
	vm.run();
	ifs.close();
}

void usage()
{
	std::cerr << "Usage: ./avm [-v] [file]\n";
	throw std::exception{}; 
}

int parse_option(int argc, char ** argv)
{
	// bit mask: file = 1, verbose = 2
	int mode = 0;
	if (argc == 2)
		mode = (std::string{argv[1]} != "-v") ? 1 : 2;
	else if (argc == 3)
	{
		if (std::string{argv[1]} != "-v")
			usage();
		mode = 3;
	}
	else if (argc > 3)
	{
		std::cerr << "Error: wrong number of arguments\n";
		usage();
	}
	return mode;
}

int main(int argc, char ** argv)
{
	try
	{
		int mode = parse_option(argc, argv);
		bool is_verbose = mode & 2;
		if (mode & 1)	vm_file_mode(is_verbose, argv[argc - 1]);
		else			vm_input_mode(is_verbose);
	}
	catch (std::exception const & e)
	{
		return 1;
	}
}
