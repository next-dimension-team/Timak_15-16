/*
 * StereotypeFactory.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "StereotypeFactory.h"

#include <OgreManualObject.h>
#include <OgreSceneNode.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../ApplicationManagement/ElementCollection.h"
#include "../DataStructure/Association.h"
#include "../Graphics/AssociationGraphics.h"
#include "../Graphics/DrawingAlgorithm.h"
#include "../Graphics/StereotypeGraphics.h"
#include "Aggregation.h"
#include "Association.h"
#include "Stereotype.h"
#include "Utilities.h"


StereotypeFactory::StereotypeFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
	this->connector = 0;
	this->stereotypeName = "";
}

StereotypeFactory::~StereotypeFactory()
{

}

Element* StereotypeFactory::factoryMethod(Association* ass, std::string stereotypeName)
{
	return NULL;//this->generalFactoryMethod(dynamic_cast<Metamodel::Association*>(ass->getData()), stereotypeName);
}

Element* StereotypeFactory::factoryMethod(Aggregation* agg, std::string stereotypeName)
{
	return NULL;//this->generalFactoryMethod(dynamic_cast<Metamodel::Association*>(agg->getData()), stereotypeName);
}

Element* StereotypeFactory::generalFactoryMethod(Metamodel::Association* connector, std::string stereotypeName)
{
	this->connector = connector;
	this->stereotypeName = stereotypeName;

	Ogre::Vector3 vecBegin = Utilities::getConnectorSourceSceneNode(this->connector)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	Ogre::Vector3 vecEnd = Utilities::getConnectorTargetSceneNode(this->connector)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	this->differenceVector = vecEnd - vecBegin;

	Stereotype* stereotype = static_cast<Stereotype*>(ElementFactory::factoryMethod());

	return stereotype;
}

Element* StereotypeFactory::getElementInstance()
{
	return new Stereotype();
}

std::string StereotypeFactory::getElementName()
{
	return "stereotype_";
}

std::string StereotypeFactory::getElementType()
{
	return Stereotype::ELEMENT_TYPE;
}

Metamodel::Element* StereotypeFactory::getElementData()
{
	Metamodel::Association* elemData = dynamic_cast<Metamodel::Association*>(this->connector);

	elemData->setStereotype(this->stereotypeName);

	return elemData;
}

ElementGraphics* StereotypeFactory::getElementGraphics(std::string name)
{
	/*Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	ElementGraphics* connectorGraphics = ElementCollection::getInstance()->findElement(this->connector)->getGraphics();
	Ogre::SceneNode* sceneNode = Utilities::getSceneNode(connector)->createChildSceneNode(name + "_node", *new Ogre::Vector3(static_cast<AssociationGraphics*>(connectorGraphics)->getLength() / 2, 0, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Stereotype::ELEMENT_TYPE);

	StereotypeGraphics* graphics = new StereotypeGraphics(manualObject, sceneNode, drawingAlgorihtm);
	graphics->setDifferenceVector(this->differenceVector);

	return graphics;*/
	return 0 ;
}

