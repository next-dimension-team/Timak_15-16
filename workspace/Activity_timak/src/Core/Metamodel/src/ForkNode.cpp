#include "../include/ForkNode.h"
#include "../include/Element.h"
#include "../include/ActivityEdge.h"

namespace team4
{
const std::string ForkNode::ELEMENT_TYPE = "ForkNode";
ForkNode::ForkNode()
{
    incoming = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

ForkNode::~ForkNode()
{}

bool ForkNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, outgoing.size());
        for (auto i: outgoing)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        writeMetamodelElement2File(A_stream, incoming);
        return true;
    }
    return false;
}
bool ForkNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
