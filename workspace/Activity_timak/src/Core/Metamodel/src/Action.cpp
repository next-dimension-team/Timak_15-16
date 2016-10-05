#include "../include/Action.h"
#include "../include/Constraint.h"

namespace team4
{
const std::string Action::ELEMENT_TYPE = "Action";

Action::Action()
{
    isLocallyReentrant = false;
    localPostcondition = NULL;
    m_Constraint = NULL;
    localPrecondition = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

Action::~Action()
{}

bool Action::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, isLocallyReentrant);
        writeMetamodelElement2File(A_stream, localPostcondition);
        writeMetamodelElement2File(A_stream, m_Constraint);
        writeMetamodelElement2File(A_stream, localPrecondition);
        return true;
    }
    return false;
}
bool Action::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        DEF_READFROMFILE1(A_stream, isLocallyReentrant);
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
