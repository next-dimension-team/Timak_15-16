#include "../include/Variable.h"

namespace team4
{
const std::string Variable::ELEMENT_TYPE = "Variable";
Variable::Variable()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Variable::~Variable()
{}

bool Variable::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        return true;
    }
    return false;
}
bool Variable::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
