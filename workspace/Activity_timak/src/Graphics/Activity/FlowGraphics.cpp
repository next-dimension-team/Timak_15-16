/*
 * FlowGraphics.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Schade
 */

#include "FlowGraphics.h"

#include <OgreManualObject.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Element.h"
#include "../../Core/Utilities.h"
#include "../../DataStructure/ControlFlow.h"
#include "../../HelperTeam4.h"





FlowGraphics::FlowGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
: ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{

}

FlowGraphics::~FlowGraphics()
{

}

void FlowGraphics::draw(const std::string& A_name)
{
	DEF_BEGIN;
	ElementGraphics::draw(A_name);
}

double FlowGraphics::getLength()
{
	DEF_BEGIN;
	//TODO TEAM4
	/*
	Metamodel::ControlFlow* flowData = dynamic_cast<Metamodel::ControlFlow*>(ElementCollection::getInstance()->findElement(manualObject->getName())->getData());
	Ogre::Vector3 targetVector = Utilities::getConnectorTargetSceneNode(flowData)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	Ogre::Vector3 sourceVector = Utilities::getConnectorSourceSceneNode(flowData)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

	return sourceVector.distance(targetVector);*/
	return 100.0;
}




