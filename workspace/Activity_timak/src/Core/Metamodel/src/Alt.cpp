#include "../include/Alt.h"

namespace team4
{
const std::string Alt::ELEMENT_TYPE = "Alt";
Alt::Alt()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Alt::~Alt()
{}

bool Alt::serialization(std::ofstream &A_stream)
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
bool Alt::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
