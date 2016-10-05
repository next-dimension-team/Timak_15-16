#include "../include/InteractionOperand.h"
#include "../include/InteractionFragment.h"

namespace team4
{
const std::string InteractionOperand::ELEMENT_TYPE = "InteractionOperand";
InteractionOperand::InteractionOperand()
{
    m_InteractionFragment = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

InteractionOperand::~InteractionOperand()
{}

bool InteractionOperand::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, m_InteractionFragment);
        return true;
    }
    return false;
}
bool InteractionOperand::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
