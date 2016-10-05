#include "../include/Behavior.h"

namespace team4
{
const std::string Behavior::ELEMENT_TYPE = "Behavior";
Behavior::Behavior()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Behavior::~Behavior()
{}

bool Behavior::serialization(std::ofstream &A_stream)
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
bool Behavior::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}