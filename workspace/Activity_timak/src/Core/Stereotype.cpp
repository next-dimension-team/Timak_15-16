/*
 * Stereotype.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */


#include "Stereotype.h"

#include <string>

#include "../DataStructure/Element.h"

const std::string Stereotype::ELEMENT_TYPE = "STEREOTYPE";

Stereotype::Stereotype() : Element()
{

}

Stereotype::~Stereotype()
{
	this->setData(new Metamodel::Element()); // temporary object to avoid double delete
}


