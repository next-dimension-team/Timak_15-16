#include "../include/MergeNode.h"
#include "../include/Element.h"
#include "../include/ActivityEdge.h"

namespace team4
{
const std::string MergeNode::ELEMENT_TYPE = "MergeNode";
MergeNode::MergeNode()
{
    outgoing = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

MergeNode::~MergeNode()
{}

bool MergeNode::serialization(std::ofstream &A_stream)
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
bool MergeNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
