#include "../include/Constraint.h"

namespace team4
{
const std::string Constraint::ELEMENT_TYPE = "Constraint";
Constraint::Constraint()
{
    setType(ELEMENT_TYPE);
    generateName();
}

Constraint::~Constraint()
{}

bool Constraint::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        return true;
    }
    return false;
}
bool Constraint::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
