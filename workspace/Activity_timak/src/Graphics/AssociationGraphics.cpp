/*
 * AssociationGraphics.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "AssociationGraphics.h"

#include <OgreManualObject.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/ElementCollection.h"
#include "../Core/Element.h"
#include "../Core/Utilities.h"
#include "../DataStructure/Association.h"


AssociationGraphics::AssociationGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
: ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{

}

AssociationGraphics::~AssociationGraphics()
{

}

void AssociationGraphics::draw(const std::string& A_name)
{
	ElementGraphics::draw(A_name);
//	Stereotype* ster = static_cast<Metamodel::Association*>(elem->getData())->getStereotype();
//	if (ster != 0) {
//		ster->draw();
//	}
}

double AssociationGraphics::getLength()
{
	//TODO TEAM4
	/*
	Metamodel::Element* data = ElementCollection::getInstance()->findElement(manualObject->getName())->getData();

	Ogre::Vector3 targetVector = Utilities::getConnectorTargetSceneNode(data)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	Ogre::Vector3 sourceVector = Utilities::getConnectorSourceSceneNode(data)->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

	return sourceVector.distance(targetVector);*/
	return 0;
}

