/*
 * AggregationAlgorithm.cpp
 *
 *  Created on: 24.6.2013
 *      Author: Schade
 */

#include "AggregationAlgorithm.h"

#include <OgreManualObject.h>
#include <OgreMath.h>
#include <OgreNode.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <cmath>

#include "../Core/Element.h"
#include "../Core/Utilities.h"
#include "ElementGraphics.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"



AggregationAlgorithm::AggregationAlgorithm() : DrawingAlgorithm()
{}
AggregationAlgorithm::~AggregationAlgorithm()
{}

void AggregationAlgorithm::draw(const std::string& A_name)
{
	DEF_BEGIN;
    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);
    Element* source = Utilities::getConnectorSource(A_name);
    Element* target = Utilities::getConnectorTarget(A_name);

    Ogre::Vector3 vecBegin =	source->getGraphics()->getConnectorBeginPoint(A_name);
    Ogre::Vector3 vecEnd =		target->getGraphics()->getConnectorEndPoint(A_name);
    Ogre::Vector3 vecDiff =		vecEnd - vecBegin;

    double len = vecBegin.distance(vecEnd);

    Ogre::ManualObject* manualObject = elem.first->getGraphics()->getManualObject();
    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);

    Ogre::Vector3 beginOrigin = source->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecBeginLocal = Ogre::Vector3(vecBegin.distance(beginOrigin), 0, 0);

    manualObject->position(vecBeginLocal);
    manualObject->position(vecBeginLocal.x + len - 6, 0, 0);

    manualObject->position(vecBeginLocal.x + len, 0, 0);
    manualObject->position(vecBeginLocal.x + len - 3, -2, 0);

    manualObject->position(vecBeginLocal.x + len, 0, 0);
    manualObject->position(vecBeginLocal.x + len - 3, 2, 0);

    manualObject->position(vecBeginLocal.x + len - 6, 0, 0);
    manualObject->position(vecBeginLocal.x + len - 3, -2, 0);

    manualObject->position(vecBeginLocal.x + len - 6, 0, 0);
    manualObject->position(vecBeginLocal.x + len - 3, 2, 0);

    manualObject->end();

    Ogre::SceneNode* node = elem.first->getGraphics()->getSceneNode();
    node->attachObject(manualObject);

    // Y-axis rotation
    if (vecDiff.z < 0)
        node->yaw(	(new Ogre:: Vector3(len, 0, 0))->angleBetween(	*(new Ogre::Vector3(vecDiff.x, 0, vecDiff.z))), Ogre::Node::TS_LOCAL); // Y
    else if (vecDiff.z > 0 || vecDiff.x != 0)
        node->yaw(	-(new Ogre:: Vector3(len, 0, 0))->angleBetween(	*(new Ogre::Vector3(vecDiff.x, 0, vecDiff.z))), Ogre::Node::TS_LOCAL); // Y

    // Z-axis rotation
    if (vecDiff.y < 0)
        node->roll(	-(new Ogre:: Vector3(len, 0, 0))->angleBetween(
                        *(new Ogre::Vector3(
                              sqrt(pow(vecDiff.x, 2)+pow(vecDiff.z, 2)),
                              vecDiff.y,
                              0))),
                    Ogre::Node::TS_LOCAL);
    else if (vecDiff.y > 0)// || vecDiff.x != 0)
        node->roll(	(new Ogre:: Vector3(len, 0, 0))->angleBetween(
                        *(new Ogre::Vector3(
                              sqrt(pow(vecDiff.x, 2)+pow(vecDiff.z, 2)),
                              vecDiff.y,
                              0))),
                    Ogre::Node::TS_LOCAL);
}
void AggregationAlgorithm::select(Element* elem)
{


}
void AggregationAlgorithm::unselected(Element* elem)
{


}
