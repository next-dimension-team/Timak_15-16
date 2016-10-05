#include "../include/Element.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include "../../../HelperTeam4.h"

namespace team4
{
void writeMetamodelElement2File(std::ofstream &A_stream, team4::MetamodelElement* A_element)
{
    if (A_element != NULL)
    {
        DEF_WRITE2FILE1(A_stream, A_element->getName());
    }
    else
    {
        DEF_WRITE2FILE1(A_stream, "-1");
    }
};
const std::string MetamodelElement::ELEMENT_TYPE = "MetamodelElement";
MetamodelElement::MetamodelElement()
{
    setType(ELEMENT_TYPE);
    generateName();
}

MetamodelElement::~MetamodelElement()
{}

MetamodelElement* MetamodelElement::allOwnedElements()
{
    return NULL;
}

bool MetamodelElement::mustBeOwned()
{
    return true;
}

std::string MetamodelElement::getName()
{
    return this->name;
}

void MetamodelElement::setName(std::string A_name)
{
    this->name = A_name;
}

std::string MetamodelElement::getType()
{
    return this->type;
}

void MetamodelElement::setType(std::string A_type)
{
    this->type = A_type;
}

void MetamodelElement::Log()
{
    std::cout << "C_ElementLOG type: " << type << " id: " << id << " name: " << name << std::endl;
}
void MetamodelElement::generateName()
{
    time_t curr=time(0);
    std::ostringstream os;
    os << getType();
    os << "_";
    os << getId();
    os << "_";
    os << curr;
    setName(os.str());
}
int MetamodelElement::getId()
{
    return id;
}

void MetamodelElement::setId(int A_id)
{
    this->id = A_id;
}

bool MetamodelElement::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        A_stream << getType() << "\n";
        A_stream << getId() << "\n";
        A_stream << getName() << "\n";
        return true;
    }
    return false;
}
bool MetamodelElement::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        A_stream >> this->type;
        A_stream >> this->id;
        A_stream  >> this->name;
        return true;
    }
    return false;
}


}
