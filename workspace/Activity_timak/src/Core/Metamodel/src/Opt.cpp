#include "../include/Opt.h"

namespace team4
{
const std::string Opt::ELEMENT_TYPE = "Opt";
Opt::Opt()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Opt::~Opt()
{}

bool Opt::serialization(std::ofstream &A_stream)
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
bool Opt::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
