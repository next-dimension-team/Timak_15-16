/*
 * AssociationFactory.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "AssociationFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../DataStructure/AggregationKind.h"
#include "../DataStructure/Association.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/Property.h"
#include "../Graphics/AssociationGraphics.h"
#include "Association.h"
#include "Class.h"
#include "Utilities.h"


AssociationFactory::AssociationFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	this->source = 0;
	this->target = 0;
}

AssociationFactory::~AssociationFactory() {

}

Element* AssociationFactory::factoryMethod(Class* source, Class* target) {
	Metamodel::Class* sourceClass = dynamic_cast<Metamodel::Class*>(source->getData());
	this->source = new Metamodel::Property();
	// team4 commnent
	//this->source->setAggregationKind(Metamodel::AggregationKind::NONE);
	this->source->setClass(sourceClass);
	sourceClass->addAttribute(this->source);

	Metamodel::Class* targetClass = dynamic_cast<Metamodel::Class*>(target->getData());
	this->target = new Metamodel::Property();
	// team4 comment
	//this->target->setAggregationKind(Metamodel::AggregationKind::NONE);
	this->target->setClass(targetClass);
	targetClass->addAttribute(this->target);

	return ElementFactory::factoryMethod();
}

Element* AssociationFactory::getElementInstance() {
	return new Association();
}

std::string AssociationFactory::getElementName() {
	return "association_";
}

std::string AssociationFactory::getElementType() {
	return Association::ELEMENT_TYPE;
}

Metamodel::Element* AssociationFactory::getElementData() {
	Metamodel::Association* elemData = new Metamodel::Association();

	elemData->addMemberEnd(source);
	elemData->addMemberEnd(target);

	return static_cast<Metamodel::Relationship*>(elemData);
}

ElementGraphics* AssociationFactory::getElementGraphics(std::string name) {
	//TODO TEAM4
	/*Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = Utilities::getSceneNode(this->source->getClass())->createChildSceneNode(name + "_node", Ogre::Vector3::ZERO);
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Association::ELEMENT_TYPE);

	return new AssociationGraphics(manualObject, sceneNode, drawingAlgorihtm);*/
	return 0;
}
