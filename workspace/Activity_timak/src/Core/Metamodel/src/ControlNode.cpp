#include "../include/ControlNode.h"

namespace team4
{
const std::string ControlNode::ELEMENT_TYPE = "ControlNode";
ControlNode::ControlNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

ControlNode::~ControlNode()
{}

bool ControlNode::serialization(std::ofstream &A_stream)
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
bool ControlNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
