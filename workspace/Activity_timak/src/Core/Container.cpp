/*
 * Container.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "Container.h"
#include "../Core/Metamodel/include/Element.h"

const std::string Container::ELEMENT_TYPE = "CONTAINER";

Container::Container() : Element()
{}

Container::~Container()
{}

void Container::addElement(const std::pair<Element*, team4::MetamodelElement*>& elem)
{
    this->elements.push_back(elem);
}

std::pair<Element*, team4::MetamodelElement*> Container::findElement(const std::string& A_elementName)
{
    for(std::vector<std::pair<Element*, team4::MetamodelElement*>>::iterator i = this->elements.begin(); i != this->elements.end(); i++)
    {
        if ((*i).second->getName().compare(A_elementName) == 0)
        {
            return *i;
        }
    }

    std::pair<Element*, team4::MetamodelElement*>(NULL, NULL);
}

std::pair<Element*, team4::MetamodelElement*> Container::findElementRecursive(const std::string& A_elementName)
{
    for(std::vector<std::pair<Element*, team4::MetamodelElement*>>::iterator i = this->elements.begin(); i != this->elements.end(); i++)
    {
        if ((*i).second->getName().compare(A_elementName) == 0)
        {
            return *i;
        }
        else
        {
            if ((*i).second->getType().compare(Container::ELEMENT_TYPE) == 0)
            {
                Container* container = dynamic_cast<Container*>((*i).first);
                if (container != NULL)
                {
                    std::pair<Element*, team4::MetamodelElement*>  element = container->findElementRecursive(A_elementName);
                    if (element.first != 0)
                    {
                        return element;
                    }
                }
            }
        }
    }
    std::pair<Element*, team4::MetamodelElement*>(NULL, NULL);
}

std::vector<std::pair<Element*, team4::MetamodelElement*>> Container::getElements()
{
    return this->elements;
}

bool Container::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
    	DEF_WRITE2FILE1(A_stream, elements.size());
    	for (auto i: elements)
    	{
    		writeMetamodelElement2File(A_stream, i.second);
    	}
        return Element::serialization(A_stream) && true;
    }
    return false;
}
bool Container::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
    	//A_stream >> this->type;
        return Element::deserialization(A_stream) && true;
    }
    return false;
}
