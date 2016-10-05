#include "../include/ActivityNode.h"
#include "../include/ActivityEdge.h"
#include "../include/Element.h"
#include "../include/ActivityGroup.h"
#include "../include/StructuredActivityNode.h"

namespace team4
{
const std::string ActivityNode::ELEMENT_TYPE = "ActivityNode";
ActivityNode::ActivityNode()
{
    instructedNode = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

ActivityNode::~ActivityNode()
{}

bool ActivityNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, instructedNode);
        DEF_WRITE2FILE1(A_stream, incoming.size());
        for (auto i: incoming)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        DEF_WRITE2FILE1(A_stream, outgoing.size());
        for (auto i: outgoing)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        DEF_WRITE2FILE1(A_stream, inGroup.size());
        for (auto i: inGroup)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        return true;
    }
    return false;
}
bool ActivityNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
