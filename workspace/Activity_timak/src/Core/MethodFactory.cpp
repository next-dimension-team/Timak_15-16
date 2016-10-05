/*
 * MethodFactory.cpp
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#include "MethodFactory.h"

#include "../DataStructure/Class.h"
#include "../DataStructure/Operation.h"
#include "Class.h"


MethodFactory::MethodFactory(DrawManager* drawManager) : ElementFactory(drawManager) {

}

MethodFactory::~MethodFactory() {

}

Element* MethodFactory::factoryMethod(Class* cla, std::string operationName) {
	Metamodel::Class* classData = dynamic_cast<Metamodel::Class*>(cla->getData());

	Metamodel::Operation* operationData = new Metamodel::Operation();
	operationData->setName(operationName);
	operationData->setClass(classData);
	classData->addOperation(operationData);

	return 0;
}

Element* MethodFactory::getElementInstance() {
	return 0;
}

std::string MethodFactory::getElementName() {
	return 0;
}

std::string MethodFactory::getElementType() {
	return 0;
}

Metamodel::Element* MethodFactory::getElementData() {
	return 0;
}

ElementGraphics* MethodFactory::getElementGraphics(std::string name) {
	return 0;
}

