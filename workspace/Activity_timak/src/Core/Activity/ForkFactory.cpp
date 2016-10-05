/*
 * ForkFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "ForkFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/ForkNode.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/ForkGraphics.h"
#include "../Container.h"
#include "Fork.h"

#include "../Metamodel/include/ForkNode.h"

ForkFactory::ForkFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
    this->container = 0;
    this->centerPoint = 0;
}

ForkFactory::~ForkFactory()
{}

Element* ForkFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
    this->centerPoint = centerPoint;
    this->container = c;

    Fork* elem = static_cast<Fork*>(ElementFactory::factoryMethod());

    // TODO TEAM4
    //this->container->addElement(elem);

    return elem;
}

Element* ForkFactory::getElementInstance()
{
    return new Fork();
}

std::string ForkFactory::getElementName()
{
    return "Fork_";
}

std::string ForkFactory::getElementType()
{
    return Fork::ELEMENT_TYPE;
}

Metamodel::Element* ForkFactory::getElementData()
{
    Metamodel::ForkNode* elemData = new Metamodel::ForkNode();

    Metamodel::Layer* l = dynamic_cast<Metamodel::Layer*>(container->getData());
    if (l)
    {
        l->addElement(elemData);
    }
    Metamodel::ActivityFragment* f = dynamic_cast<Metamodel::ActivityFragment*>(container->getData());
    if (f)
    {
        f->addElement(elemData);
    }

    return elemData;
}

ElementGraphics* ForkFactory::getElementGraphics(std::string name)
{
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::ForkNode::ELEMENT_TYPE);

    return new ForkGraphics(manualObject, sceneNode, drawingAlgorihtm);
}


