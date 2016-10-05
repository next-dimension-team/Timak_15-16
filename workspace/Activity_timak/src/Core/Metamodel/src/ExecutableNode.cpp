#include "../include/ExecutableNode.h"

namespace team4
{
const std::string ExecutableNode::ELEMENT_TYPE = "ExecutableNode";
ExecutableNode::ExecutableNode()
{
    setType(ELEMENT_TYPE);
    generateName();
    executable = "";
}

ExecutableNode::~ExecutableNode()
{}

bool ExecutableNode::serialization(std::ofstream &A_stream)
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
bool ExecutableNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
