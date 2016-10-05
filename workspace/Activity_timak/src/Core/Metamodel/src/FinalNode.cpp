#include "../include/FinalNode.h"

namespace team4
{
const std::string FinalNode::ELEMENT_TYPE = "FinalNode";
FinalNode::FinalNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

FinalNode::~FinalNode()
{}

bool FinalNode::serialization(std::ofstream &A_stream)
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
bool FinalNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
