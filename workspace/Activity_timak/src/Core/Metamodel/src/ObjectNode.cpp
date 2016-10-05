#include "../include/ObjectNode.h"

namespace team4
{
const std::string ObjectNode::ELEMENT_TYPE = "ObjectNode";
ObjectNode::ObjectNode()
{
    setType(ELEMENT_TYPE);
    generateName();
}

ObjectNode::~ObjectNode()
{}

bool ObjectNode::serialization(std::ofstream &A_stream)
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
bool ObjectNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
