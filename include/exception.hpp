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
    virtual const char * what() const noexcept;

private:
    std::string str;
};

/*
# Parsing errors

# Runtime erros:
Division by zero
Modulo by zero
Overflow
Underflow
Empty stack
+ StackSizeLessThanTwo
Assertion false
Print type isn't int8

Can I just polymorphism catch one and then done?
I can diff with parsing errors and runtime errors
That should be enough

1. use map instead of switch with how I run operation
2. generalize binary operation
3. add StackSizeLessThanTwo exception
4. differentiate exceptions
*/
