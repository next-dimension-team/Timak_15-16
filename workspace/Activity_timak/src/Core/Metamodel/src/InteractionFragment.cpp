#include "../include/InteractionFragment.h"

namespace team4
{
const std::string InteractionFragment::ELEMENT_TYPE = "InteractionFragment";
InteractionFragment::InteractionFragment()
{
    setType(ELEMENT_TYPE);
    generateName();
}

InteractionFragment::~InteractionFragment()
{}

bool InteractionFragment::serialization(std::ofstream &A_stream)
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
bool InteractionFragment::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
