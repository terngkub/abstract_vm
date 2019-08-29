#pragma once
#include <exception>
#include <string>

class AvmException : public std::exception
{
public:
    AvmException(std::string str);
    ~AvmException();
    virtual const char * what() const noexcept;

private:
    std::string str;

    // unimplemented
    AvmException();
    AvmException(AvmException const & src);
    AvmException & operator=(AvmException const & rhs);
};