#include "../include/JoinNode.h"
#include "../include/ActivityEdge.h"

namespace team4
{
const std::string JoinNode::ELEMENT_TYPE = "JoinNode";

JoinNode::JoinNode()
{
    outgoing = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

JoinNode::~JoinNode()
{}

bool JoinNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, incoming.size());
        for (auto i: incoming)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        writeMetamodelElement2File(A_stream, outgoing);

        return true;
    }
    return false;
}
bool JoinNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
