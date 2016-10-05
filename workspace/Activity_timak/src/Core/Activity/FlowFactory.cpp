/*
 * FlowFactory.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "FlowFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
//#include "../../DataStructure/ActivityNode.h"
#include "../../DataStructure/ControlFlow.h"
#include "../../Graphics/Activity/FlowGraphics.h"

#include "../Metamodel/include/ActivityNode.h"
#include "../Metamodel/include/Element.h"
#include "../Metamodel/include/FlowFinalNode.h"
#include "../../HelperTeam4.h"

#include "../Utilities.h"
#include "Flow.h"


FlowFactory::FlowFactory(DrawManager* drawManager) :
        ElementFactory(drawManager)
{
    this->source = 0;
    this->target = 0;
}

FlowFactory::~FlowFactory()
{}

Element* FlowFactory::factoryMethod(std::pair<Element*, team4::MetamodelElement*>& A_source, std::pair<Element*, team4::MetamodelElement*>& A_target)
{
    return factoryMethod( dynamic_cast<team4::ActivityNode*>(A_source.second), dynamic_cast<team4::ActivityNode*>(A_target.second));
}

Element* FlowFactory::factoryMethod(team4::ActivityNode* A_source, team4::ActivityNode* A_target)
{
    this->source = A_source;
    this->target = A_target;
    return  ElementFactory::factoryMethod();
}

Element* FlowFactory::getElementInstance()
{
    return new Flow();
}

std::string FlowFactory::getElementName()
{
    return "flow_";
}

std::string FlowFactory::getElementType()
{
    return Flow::ELEMENT_TYPE;
}

Metamodel::Element* FlowFactory::getElementData()
{
    /*Metamodel::ControlFlow* elemData = new Metamodel::ControlFlow();

    elemData->setSource(source);
    elemData->setTarget(target);*/

    return 0;
}

ElementGraphics* FlowFactory::getElementGraphics(std::string name)
{
    DEF_BEGIN;
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    if (manualObject == NULL)
        DEF_ERROR("manualObject is null");
    DEFL;

    Ogre::SceneNode* sceneNode = Utilities::getSceneNode(this->source->getName())->createChildSceneNode(name + "_node", Ogre::Vector3::ZERO);
    if (sceneNode == NULL)
        DEF_ERROR("sceneNode is null");
    DEFL;

    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::FlowFinalNode::ELEMENT_TYPE);
    if (drawingAlgorihtm == NULL)
        DEF_ERROR("drawingAlgorihtm is null");
    DEFL;

    FlowGraphics* temp = new FlowGraphics(manualObject, sceneNode, drawingAlgorihtm);
    if (temp == NULL)
        DEF_ERROR("temp is null");
    DEFL;

    return temp;
}

