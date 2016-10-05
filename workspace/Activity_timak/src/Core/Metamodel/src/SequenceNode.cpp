#include "../include/SequenceNode.h"

namespace team4
{
const std::string SequenceNode::ELEMENT_TYPE = "SequenceNode";
SequenceNode::SequenceNode()
{
    m_ExecutableNode = NULL;
    executableNode = NULL;

    setType(ELEMENT_TYPE);
    generateName();
}

SequenceNode::~SequenceNode()
{}

bool SequenceNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, m_ExecutableNode);
        writeMetamodelElement2File(A_stream, executableNode);
        return true;
    }
    return false;
}
bool SequenceNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
