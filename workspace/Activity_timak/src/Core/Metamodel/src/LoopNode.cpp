#include "../include/LoopNode.h"

namespace team4
{
const std::string LoopNode::ELEMENT_TYPE = "LoopNode";
LoopNode::LoopNode()
{
	init = "";
	cond = "";
    isTestedFirst = false;
    decider = false;
    setType(ELEMENT_TYPE);
    //elements = NULL;
    generateName();
}

LoopNode::~LoopNode()
{}

bool LoopNode::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, init);
        DEF_WRITE2FILE1(A_stream, cond);
        DEF_WRITE2FILE2(A_stream, isTestedFirst, decider);
        DEF_WRITE2FILE1(A_stream, test.size());
        for (auto i: test)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        DEF_WRITE2FILE1(A_stream, setup.size());
        for (auto i: setup)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        DEF_WRITE2FILE1(A_stream, body.size());
        for (auto i: body)
        {
            writeMetamodelElement2File(A_stream, i);
        }
        DEF_WRITE2FILE1(A_stream, elements.size());
        for (auto i: elements)
                        {
                        	DEF_WRITE2FILE1(A_stream, i);
                        }
        return true;
    }
    return false;
}
bool LoopNode::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
