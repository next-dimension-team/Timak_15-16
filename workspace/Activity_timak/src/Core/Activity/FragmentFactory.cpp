/*
 * FragmentFactory.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#include "FragmentFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/FragmentGraphics.h"
#include "Fragment.h"
#include "FragmentCollection.h"
#include "../Metamodel/include/StructuredActivityNode.h"


FragmentFactory::FragmentFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
	this->container = 0;
	this->centerPoint = 0;
	this->fragmentCollection = 0;
}

FragmentFactory::~FragmentFactory() {}

Element* FragmentFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint, int width, int height)
{
	//this->centerPoint = centerPoint;
	//this->container = c;
	//this->fragmentCollection = (f != 0) ? f->fragmentCollection : 0;

	//this->fragmentType = fragmentType;
	//this->fragmentCondition = fragmentCondition;

	//team4::StructuredActivityNode* elem = static_cast<team4::StructuredActivityNode*>(ElementFactory::factoryMethod());

	//this->container->addElement(elem);

	//elem->fragmentCollection->add(elem);

	//return elem;

	this->centerPoint = centerPoint;
	this->container = c;
	this->width = width;
	this->height = height;
	Element* elem = static_cast<Element*>(ElementFactory::factoryMethod());

	// TODO TEAM4
	    //this->container->addElement(elem);

	return elem;
}

Element* FragmentFactory::getElementInstance()
{
	Fragment* f = new Fragment();
	f->fragmentCollection = (this->fragmentCollection == 0) ? new FragmentCollection() : this->fragmentCollection;

	return f;
}

std::string FragmentFactory::getElementName()
{
	return "fragment_";
}

std::string FragmentFactory::getElementType()
{
	return Fragment::ELEMENT_TYPE;
}

Metamodel::Element* FragmentFactory::getElementData()
{
	Metamodel::ActivityFragment* elemData = new Metamodel::ActivityFragment();

	elemData->setFragmentCondition(this->fragmentCondition);
	elemData->setFragmentType(this->fragmentType);

	Metamodel::Layer* l = dynamic_cast<Metamodel::Layer*>(container->getData());
	if (l) {
		l->addElement(elemData);
	}

	return elemData;
}

ElementGraphics* FragmentFactory::getElementGraphics(std::string name)
{
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Fragment::ELEMENT_TYPE);

	Ogre::ManualObject* bookmarkManualObject = drawManager->createManualObject("BM_" + name);

	return new FragmentGraphics(manualObject, sceneNode, drawingAlgorihtm, bookmarkManualObject,this->width,this->height);
}
