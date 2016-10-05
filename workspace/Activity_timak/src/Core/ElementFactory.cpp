/*
 * ElementFactory.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "ElementFactory.h"

#include <sstream>

#include "Element.h"
#include "../HelperTeam4.h"


ElementFactory::ElementFactory(DrawManager* drawManager)
{
	this->drawManager = drawManager;
	this->maxId = 0;
}

ElementFactory::~ElementFactory()
{

}

Element* ElementFactory::factoryMethod()
{
	DEF_BEGIN;
	Element* elem = createElement();
	elem = initializeElement(elem);
	elem = assignElementData(elem);
	elem = assignElementGraphics(elem);

	return elem;
}

Element* ElementFactory::createElement()
{
	Element* elem = getElementInstance();
	elem->setId(idManager());

	return elem;
}

Element* ElementFactory::initializeElement(Element* elem)
{
	std::ostringstream os;
	os << getElementName();
	os << elem->getId();
	elem->setName(os.str());

	elem->setType(getElementType());

	return elem;
}

Element* ElementFactory::assignElementData(Element* elem)
{
	Metamodel::Element* data = getElementData();
	elem->setData(data);
	return elem;
}

Element* ElementFactory::assignElementGraphics(Element* elem)
{
	DEF_BEGIN;
	elem->setGraphics(getElementGraphics(elem->getName()));

	return elem;
}

int ElementFactory::idManager(void)
{
	return maxId++;
}

Element* ElementFactory::getElementInstance() { return 0; }
std::string ElementFactory::getElementName() { return 0; }
std::string ElementFactory::getElementType() { return 0; }
Metamodel::Element* ElementFactory::getElementData() { return 0; }
ElementGraphics* ElementFactory::getElementGraphics(std::string name) { DEF_BEGIN; return 0; }
