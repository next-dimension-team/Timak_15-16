/*
 * AttributeFactory.cpp
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#include "AttributeFactory.h"

#include <string>

#include "../DataStructure/Class.h"
#include "../DataStructure/Property.h"
#include "Class.h"


AttributeFactory::AttributeFactory(DrawManager* drawManager) : ElementFactory(drawManager) {

}

AttributeFactory::~AttributeFactory() {

}

Element* AttributeFactory::factoryMethod(Class* cla, std::string attributeName) {
	Metamodel::Class* classData = dynamic_cast<Metamodel::Class*>(cla->getData());

	Metamodel::Property* propertyData = new Metamodel::Property();
	propertyData->setName(attributeName);
	propertyData->setClass(classData);
	classData->addAttribute(propertyData);

	return 0;
}

Element* AttributeFactory::getElementInstance() {
	return 0;
}

std::string AttributeFactory::getElementName() {
	return 0;
}

std::string AttributeFactory::getElementType() {
	return 0;
}

Metamodel::Element* AttributeFactory::getElementData() {
	return 0;
}

ElementGraphics* AttributeFactory::getElementGraphics(std::string name) {
	return 0;
}

