#include "../include/Activity.h"
#include "../include/ActivityNode.h"
#include "../include/ActivityEdge.h"

namespace team4
{
const std::string Activity::ELEMENT_TYPE = "Activity";
Activity::Activity()
{
    isReadOnly = false;
    isSingleExecution = false;
    node = NULL;
    edge = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

Activity::~Activity()
{}

bool Activity::serialization( std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE2(A_stream, isReadOnly, isSingleExecution);
        writeMetamodelElement2File(A_stream, node);
        writeMetamodelElement2File(A_stream, edge);
        return true;
    }
    return false;
}
bool Activity::deserialization( std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
