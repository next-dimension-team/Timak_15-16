/*
 * ClassFactory.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "ClassFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/Layer.h"
#include "../Graphics/ClassGraphics.h"
#include "Class.h"
#include "Layer.h"


ClassFactory::ClassFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
	this->lay = 0;
	this->className = "";
	this->centerPoint = 0;
}

ClassFactory::~ClassFactory()
{

}

Element* ClassFactory::factoryMethod(Layer* lay, std::string className, Ogre::Vector2* centerPoint)
{
	this->className = className;
	this->centerPoint = centerPoint;
	this->lay = lay;

	Class* elem = static_cast<Class*>(ElementFactory::factoryMethod());

	lay->addClass(elem);

	return elem;
}

Element* ClassFactory::getElementInstance()
{
	return new Class();
}

std::string ClassFactory::getElementName()
{
	return "class_";
}

std::string ClassFactory::getElementType()
{
	return Class::ELEMENT_TYPE;
}

Metamodel::Element* ClassFactory::getElementData()
{
	Metamodel::Class* elemData = new Metamodel::Class();

	elemData->setName(className);

	Metamodel::Layer* l = dynamic_cast<Metamodel::Layer*>(lay->getData());
	if (l) {
		l->addElement(elemData);
	}

	return elemData;
}

ElementGraphics* ClassFactory::getElementGraphics(std::string name)
{
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = this->lay->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Class::ELEMENT_TYPE);

	return new ClassGraphics(manualObject, sceneNode, drawingAlgorihtm);
}

