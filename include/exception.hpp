#pragma once
#include <exception>
#include <string>

class AvmException : public std::exception
{
    std::string str;

    AvmException();
    AvmException(AvmException const & src);
    AvmException & operator=(AvmException const & rhs);

public:
    AvmException(std::string str);
    ~AvmException();
    virtual const char * what() const noexcept;
};