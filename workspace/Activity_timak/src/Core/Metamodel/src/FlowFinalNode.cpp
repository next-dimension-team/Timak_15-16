#include "../include/FlowFinalNode.h"

namespace team4
{
const std::string FlowFinalNode::ELEMENT_TYPE = "FlowFinalNode";
FlowFinalNode::FlowFinalNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

FlowFinalNode::~FlowFinalNode()
{}

bool FlowFinalNode::serialization(std::ofstream &A_stream)
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
bool FlowFinalNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
