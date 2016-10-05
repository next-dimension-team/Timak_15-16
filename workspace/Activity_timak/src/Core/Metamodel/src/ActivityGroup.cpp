#include "../include/ActivityGroup.h"
#include <stdlib.h>

namespace team4
{
const std::string ActivityGroup::ELEMENT_TYPE = "ActivityGroup";
ActivityGroup::ActivityGroup()
{
    m_ActivityGroup = NULL;
    setType(ELEMENT_TYPE);
    generateName();
}

ActivityGroup::~ActivityGroup()
{}

bool ActivityGroup::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        writeMetamodelElement2File(A_stream, m_ActivityGroup);
        return true;
    }
    return false;
}
bool ActivityGroup::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
