/*
 * AggregationFactory.cpp
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#include "AggregationFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../DataStructure/AggregationKind.h"
#include "../DataStructure/Association.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/Property.h"
#include "../Graphics/AssociationGraphics.h"
#include "Aggregation.h"
#include "Class.h"
#include "Utilities.h"


AggregationFactory::AggregationFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	this->source = 0;
	this->target = 0;
}

AggregationFactory::~AggregationFactory() {

}

Element* AggregationFactory::factoryMethod(Class* source, Class* target) {
	Metamodel::Class* sourceClass = dynamic_cast<Metamodel::Class*>(source->getData());
	this->source = new Metamodel::Property();
	// team4 comment
	//this->source->setAggregationKind(Metamodel::AggregationKind::NONE);
	this->source->setClass(sourceClass);
	sourceClass->addAttribute(this->source);

	Metamodel::Class* targetClass = dynamic_cast<Metamodel::Class*>(target->getData());
	this->target = new Metamodel::Property();
	// team4 comment
	//this->target->setAggregationKind(Metamodel::AggregationKind::SHARED);
	this->target->setClass(targetClass);
	targetClass->addAttribute(this->target);

	return ElementFactory::factoryMethod();
}

Element* AggregationFactory::getElementInstance() {
	return new Aggregation();
}

std::string AggregationFactory::getElementName() {
	return "aggregation_";
}

std::string AggregationFactory::getElementType() {
	return Aggregation::ELEMENT_TYPE;
}

Metamodel::Element* AggregationFactory::getElementData() {
	Metamodel::Association* elemData = new Metamodel::Association();

	elemData->addMemberEnd(source);
	elemData->addMemberEnd(target);

	return static_cast<Metamodel::Relationship*>(elemData);
}

ElementGraphics* AggregationFactory::getElementGraphics(std::string name) {
	/*Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Metamodel::Class* c = this->source->getClass();
	Ogre::SceneNode* sceneNode = Utilities::getSceneNode(c)->createChildSceneNode(name + "_node", Ogre::Vector3::ZERO);
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Aggregation::ELEMENT_TYPE);

	return new AssociationGraphics(manualObject, sceneNode, drawingAlgorihtm);*/
	return 0;
}
