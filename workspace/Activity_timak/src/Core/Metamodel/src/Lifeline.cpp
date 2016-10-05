#include "../include/Lifeline.h"
#include "../include/InteractionFragment.h"

namespace team4
{
const std::string Lifeline::ELEMENT_TYPE = "Lifeline";
Lifeline::Lifeline()
{
    m_InteractionFragment = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

Lifeline::~Lifeline()
{}

bool Lifeline::serialization(std::ofstream &A_stream)
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
bool Lifeline::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
