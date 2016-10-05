/*
 * InitialNodeFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "InitialNodeFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/InitialNode.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/NodeGraphics.h"
#include "../Container.h"
#include "InitialNode.h"

#include "../../HelperTeam4.h"


InitialNodeFactory::InitialNodeFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	this->centerPoint = 0;
	this->container = 0;
}

InitialNodeFactory::~InitialNodeFactory() {}

Element* InitialNodeFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
	this->centerPoint = centerPoint;
	this->container = c;

	InitialNode* elem = static_cast<InitialNode*>(ElementFactory::factoryMethod());

	// TODO TEAM4
	    //this->container->addElement(elem);

	return elem;
}

Element* InitialNodeFactory::getElementInstance()
{
	return new InitialNode();
}

std::string InitialNodeFactory::getElementName()
{
	return "InitialNode_";
}

std::string InitialNodeFactory::getElementType()
{
	return InitialNode::ELEMENT_TYPE;
}

Metamodel::Element* InitialNodeFactory::getElementData()
{
	Metamodel::InitialNode* elemData = new Metamodel::InitialNode();

	Metamodel::Layer* l = dynamic_cast<Metamodel::Layer*>(container->getData());
	if (l) {
		l->addElement(elemData);
	}
	Metamodel::ActivityFragment* f = dynamic_cast<Metamodel::ActivityFragment*>(container->getData());
	if (f) {
		f->addElement(elemData);
	}

	return elemData;
}

ElementGraphics* InitialNodeFactory::getElementGraphics(std::string name)
{
	DEF_BEGIN;
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(InitialNode::ELEMENT_TYPE);

	return new NodeGraphics(manualObject, sceneNode, drawingAlgorihtm);
}


