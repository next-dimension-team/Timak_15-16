/*
 * DecisionFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "DecisionFactory.h"
#include "../Metamodel/include/DecisionNode.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/DecisionGraphics.h"
#include "../Container.h"
#include "Decision.h"

DecisionFactory::DecisionFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
    this->container = 0;
    this->centerPoint = 0;
}

DecisionFactory::~DecisionFactory()
{}

Element* DecisionFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
    this->centerPoint = centerPoint;
    this->container = c;

    Element* elem = static_cast<Element*>(ElementFactory::factoryMethod());

    // TODO TEAM4
        //this->container->addElement(elem);

    return elem;
}

Element* DecisionFactory::getElementInstance()
{
    return new Decision();
}

std::string DecisionFactory::getElementName()
{
    return "decision_";
}

std::string DecisionFactory::getElementType()
{
    return Decision::ELEMENT_TYPE;
}

Metamodel::Element* DecisionFactory::getElementData()
{
    /*Metamodel::DecisionNode* elemData = new Metamodel::DecisionNode();

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

    return elemData;*/
	return 0;
}

ElementGraphics* DecisionFactory::getElementGraphics(std::string name)
{
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::DecisionNode::ELEMENT_TYPE);

    return new DecisionGraphics(manualObject, sceneNode, drawingAlgorihtm);
}


