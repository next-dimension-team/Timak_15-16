/*
 * ContainerFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "ContainerFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../Graphics/ContainerGraphics.h"
#include "Container.h"


ContainerFactory::ContainerFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	this->elem = 0;
	this->centerPoint = 0;
}

ContainerFactory::~ContainerFactory() {}

Element* ContainerFactory::factoryMethod(Element* elemPar, Ogre::Vector2* centerPoint) {
	this->centerPoint = centerPoint;
	this->elem = elemPar;

	return static_cast<Container*>(ElementFactory::factoryMethod());
}

Element* ContainerFactory::getElementInstance() {
	return new Container();
}

std::string ContainerFactory::getElementName() {
	return "container_";
}

std::string ContainerFactory::getElementType() {
	return Container::ELEMENT_TYPE;
}

Metamodel::Element* ContainerFactory::getElementData() {
	return 0;
}

ElementGraphics* ContainerFactory::getElementGraphics(std::string name) {
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = this->elem->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Container::ELEMENT_TYPE);

	return new ContainerGraphics(manualObject, sceneNode, drawingAlgorihtm);
}


