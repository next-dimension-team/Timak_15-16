#include "../include/StructuredActivityNode.h"
#include "../include/ActivityEdge.h"
#include "../include/Variable.h"

namespace team4
{
const std::string StructuredActivityNode::ELEMENT_TYPE = "StructuredActivityNode";
StructuredActivityNode::StructuredActivityNode()
{
    mustIsolate = false;
    node = NULL;
    variable = NULL;
    edge = NULL;
   // elements = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

StructuredActivityNode::~StructuredActivityNode()
{}

bool StructuredActivityNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, mustIsolate);
        writeMetamodelElement2File(A_stream, node);
        writeMetamodelElement2File(A_stream, variable);
        writeMetamodelElement2File(A_stream, edge);
        return true;
    }
    return false;
}
bool StructuredActivityNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
