#include "a_int8.h"
#include <stdexcept>      // std::invalid_argument
using namespace CX2::Memory::Vars;

A_INT8::A_INT8()
{
    value = 0;
    setVarType(ABSTRACT_INT8);
}

int8_t A_INT8::getValue()
{
    return value;
}

bool A_INT8::setValue(int8_t value)
{
    this->value = value;
    return true;
}

std::string A_INT8::toString()
{
    return std::to_string(value);
}

bool A_INT8::fromString(const std::string &value)
{
    if (value.empty())
    {
        this->value = 0;
        return true;
    }
    this->value = static_cast<int8_t>(strtol( value.c_str(), nullptr, 10 ));
    if (value!="0" && this->value==0) return false;

    return true;
}

Abstract *A_INT8::protectedCopy()
{
    A_INT8 * var = new A_INT8;
    if (var) *var = this->value;
    return var;
}
