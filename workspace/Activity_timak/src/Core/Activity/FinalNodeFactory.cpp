/*
 * FinalNodeFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "FinalNodeFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/FinalNode.h"
#include "../../Graphics/Activity/NodeGraphics.h"
#include "../Container.h"
#include "FinalNode.h"


FinalNodeFactory::FinalNodeFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	this->centerPoint = 0;
	this->container = 0;
}

FinalNodeFactory::~FinalNodeFactory() {}

Element* FinalNodeFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
	this->centerPoint = centerPoint;
	this->container = c;

	FinalNode* elem = static_cast<FinalNode*>(ElementFactory::factoryMethod());

	// TODO TEAM4
	//this->container->addElement(elem);

	return elem;
}

Element* FinalNodeFactory::getElementInstance()
{
	return new FinalNode();
}

std::string FinalNodeFactory::getElementName()
{
	return "FinalNode_";
}

std::string FinalNodeFactory::getElementType()
{
	return FinalNode::ELEMENT_TYPE;
}

Metamodel::Element* FinalNodeFactory::getElementData()
{
	Metamodel::FinalNode* elemData = new Metamodel::FinalNode();
	return elemData;
}

ElementGraphics* FinalNodeFactory::getElementGraphics(std::string name)
{
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(FinalNode::ELEMENT_TYPE);

	return new NodeGraphics(manualObject, sceneNode, drawingAlgorihtm);
}


