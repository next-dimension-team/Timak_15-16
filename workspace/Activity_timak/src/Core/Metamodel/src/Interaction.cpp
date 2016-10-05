#include "../include/Interaction.h"
#include "../include/Action.h"
#include "../include/Lifeline.h"

namespace team4
{
const std::string Interaction::ELEMENT_TYPE = "Interaction";
Interaction::Interaction()
{
    m_Lifeline = NULL;
    m_Action = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

Interaction::~Interaction()
{}

bool Interaction::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, m_Lifeline);
        writeMetamodelElement2File(A_stream, m_Action);
        return true;
    }
    return false;
}
bool Interaction::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
