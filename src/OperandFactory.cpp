#include "OperandFactory.hpp"

IOperand const * OperandFactory::createInt8(std::string const & value) const
{

}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
    
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
    
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
    
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
    
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
    return (this->*func_ptr[type])(value);
}

OperandFactory::OperandFactory() :
    operand_list{}
{
    func_ptr[Int8] = &OperandFactory::createInt8;
    func_ptr[Int16] = &OperandFactory::createInt8;
    func_ptr[Int32] = &OperandFactory::createInt8;
    func_ptr[Float] = &OperandFactory::createInt8;
    func_ptr[Double] = &OperandFactory::createInt8;
}

OperandFactory::~OperandFactory()
{
    for (auto * elem : operand_list)
        delete elem;
}