#include "../include/CombinedFragment.h"
#include "../include/InteractionOperand.h"
#include "../include/InteractionOperator.h"

namespace team4
{
const std::string CombinedFragment::ELEMENT_TYPE = "CombinedFragment";

CombinedFragment::CombinedFragment()
{
    m_InteractionOperand = NULL;
    _operator = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

CombinedFragment::~CombinedFragment()
{}

bool CombinedFragment::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, m_InteractionOperand);
        //writeMetamodelElement2File(A_stream, _operator);
        return true;
    }
    return false;
}
bool CombinedFragment::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
