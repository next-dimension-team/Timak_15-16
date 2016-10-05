#include "../include/ConditionNode.h"
#include "../include/Clause.h"

namespace team4
{
const std::string ConditionNode::ELEMENT_TYPE = "ConditionNode";
ConditionNode::ConditionNode()
{
    isAssured = false;
    isDeterminate = false;
    //cluase = NULL;
    m_Clause = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

ConditionNode::~ConditionNode()
{}

bool ConditionNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE2(A_stream, isAssured, isAssured);
        DEF_WRITE2FILE1(A_stream, cluase.size());
        for (auto i: cluase)
        {
            writeMetamodelElement2File(A_stream, i);
        }
                DEF_WRITE2FILE1(A_stream, elements.size());
                for (auto i: elements)
                {
                	DEF_WRITE2FILE1(A_stream, i);
                }
        writeMetamodelElement2File(A_stream, m_Clause);
        return true;
    }
    return false;
}
bool ConditionNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
