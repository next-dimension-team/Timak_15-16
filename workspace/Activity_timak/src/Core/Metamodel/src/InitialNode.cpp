#include "../include/InitialNode.h"

namespace team4
{
const std::string InitialNode::ELEMENT_TYPE = "InitialNode";
InitialNode::InitialNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

InitialNode::~InitialNode()
{}

bool InitialNode::serialization(std::ofstream &A_stream)
{
    DEF_BEGIN;
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
bool InitialNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
