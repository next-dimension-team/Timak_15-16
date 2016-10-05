#include "../include/Par.h"

namespace team4
{
const std::string Par::ELEMENT_TYPE = "Par";
Par::Par()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Par::~Par()
{}

bool Par::serialization(std::ofstream &A_stream)
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
bool Par::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
