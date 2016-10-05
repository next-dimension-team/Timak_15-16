/*
 * ActivityFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "ActivityFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/Action.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/ActivityGraphics.h"
#include "../Container.h"
#include "Activity.h"

#include "../../Core/Metamodel/include/ActivityNode.h"


ActivityFactory::ActivityFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
    this->container = 0;
    this->activityName = "";
    this->centerPoint = 0;
}

ActivityFactory::~ActivityFactory()
{}

Element* ActivityFactory::factoryMethod(Container* c, std::string activityName, Ogre::Vector2* centerPoint)
{
    this->activityName = activityName;
    this->centerPoint = centerPoint;
    this->container = c;

    Activity* elem = static_cast<Activity*>(ElementFactory::factoryMethod());

    //todo TEAM4
    //this->container->addElement(elem);

    return elem;
}

Element* ActivityFactory::getElementInstance()
{
    return new Activity();
}

std::string ActivityFactory::getElementName()
{
    return "activity_";
}

std::string ActivityFactory::getElementType()
{
    return Activity::ELEMENT_TYPE;
}

Metamodel::Element* ActivityFactory::getElementData()
{
    Metamodel::Action* elemData = new Metamodel::Action();

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

    elemData->setName(activityName);

    return elemData;
}

ElementGraphics* ActivityFactory::getElementGraphics(std::string name)
{
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::ActivityNode::ELEMENT_TYPE);

    return new ActivityGraphics(manualObject, sceneNode, drawingAlgorihtm);
}
