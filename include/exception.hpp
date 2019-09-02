#pragma once
#include <exception>
#include <string>

class AvmException : public std::exception
{
public:
    // Constructor
    AvmException() = delete;
    AvmException(std::string str);

    // Destructor
    ~AvmException() = default;

    // Copy - enable
    AvmException(AvmException const &) = default;
    AvmException & operator=(AvmException const &) = default;

    // Move - enable
    AvmException(AvmException &&) = default;
    AvmException & operator=(AvmException &&) = default;

    // Public Methods
    const char * what() const noexcept;

private:
    std::string str;
};