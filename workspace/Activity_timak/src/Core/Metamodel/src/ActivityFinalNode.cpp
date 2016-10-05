#include "../include/ActivityFinalNode.h"

namespace team4
{
const std::string ActivityFinalNode::ELEMENT_TYPE = "ActivityFinalNode";
ActivityFinalNode::ActivityFinalNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

ActivityFinalNode::~ActivityFinalNode()
{}

bool ActivityFinalNode::serialization(std::ofstream &A_stream)
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
bool ActivityFinalNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}

}
