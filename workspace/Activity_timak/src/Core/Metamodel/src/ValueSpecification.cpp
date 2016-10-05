#include "../include/ValueSpecification.h"

namespace team4
{
const std::string ValueSpecification::ELEMENT_TYPE = "ValueSpecification";
ValueSpecification::ValueSpecification(const std::string &A_value) : _value(A_value)
{
    _value = "";
    setType(ELEMENT_TYPE);
    generateName();
}

ValueSpecification::~ValueSpecification()
{}

void ValueSpecification::set(const std::string &A_value)
{
    _value = A_value;
}
std::string ValueSpecification::get()
{
    return _value;
}

bool ValueSpecification::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, _value);
        return true;
    }
    return false;
}
bool ValueSpecification::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}


}
