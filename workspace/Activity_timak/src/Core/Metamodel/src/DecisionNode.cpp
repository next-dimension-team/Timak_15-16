#include "../include/DecisionNode.h"
#include "../include/Element.h"
#include "../include/ActivityEdge.h"

namespace team4
{
const std::string DecisionNode::ELEMENT_TYPE = "DecisionNode";
DecisionNode::DecisionNode()
{
    incoming = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

DecisionNode::~DecisionNode()
{}

bool DecisionNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, incoming);

        return true;
    }
    return false;
}
bool DecisionNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
