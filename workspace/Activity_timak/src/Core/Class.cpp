/*
 * Class.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#include "../DataStructure/Class.h"
#include "Class.h"


const std::string Class::ELEMENT_TYPE = "CLASS";

Class::Class() : Element() {  }
Class::~Class() {  }


std::string Class::getAttributesText()
{
	std::vector<Metamodel::Property*> attributes = dynamic_cast<Metamodel::Class*>(this->getData())->getAttributes();
	std::string s = "";
	std::vector<Metamodel::Property*>::const_iterator ci;
	unsigned int i;
	for(i=0; i < attributes.size(); i++)
	{
		s.append(attributes[i]->getName());
		s.append("\n");
	}
	return s;
}

std::string Class::getMethodsText()
{
	std::vector<Metamodel::Operation*> methods = dynamic_cast<Metamodel::Class*>(this->getData())->getOperations();
	std::string s = "";
	std::vector<Metamodel::Operation*>::const_iterator ci;
	unsigned int i;
	for(i=0; i < methods.size(); i++)
	{
		s.append(methods[i]->getName());
		s.append("\n");
	}
	return s;
}

