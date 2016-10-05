#include "../include/InteractionOperator.h"

namespace team4
{
const std::string InteractionOperator::ELEMENT_TYPE = "InteractionOperator";
InteractionOperator::InteractionOperator()
{
    setType(ELEMENT_TYPE);
    generateName();
}

InteractionOperator::~InteractionOperator()
{}

bool InteractionOperator::serialization(std::ofstream &A_stream)
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
bool InteractionOperator::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
