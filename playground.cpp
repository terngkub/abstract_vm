#include <iostream>
#include <fstream>

int main()
{
    std::ifstream file;
    try
    {
        file.open("playgroun.cpp");
    }
    catch (std::exception & e)
    {
        std::cerr << "Error: " << e.what();
        return 1;
    }
    
    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    file.close();
}