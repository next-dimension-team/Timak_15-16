/*
 * ClassGraphics.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "ClassGraphics.h"

#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../Core/Element.h"
#include "../Core/Utilities.h"
#include "ClassAlgorithm.h"


ClassGraphics::ClassGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
: ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{

}

ClassGraphics::~ClassGraphics()
{

}

Ogre::Vector3 ClassGraphics::getConnectorBeginPoint(const std::string& A_name)
{
	/*Element* source = Utilities::getConnectorSource(connectorData);
	Element* target = Utilities::getConnectorTarget(connectorData);

	Ogre::SceneNode* endNode = target->getGraphics()->getSceneNode();

	if (endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
		return ElementGraphics::getConnectorBeginPoint(A_name);

	double x = 0;
	double y = 0;

	Ogre::Vector3 vecBeginLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	Ogre::Vector3 vecEndLocal = endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

	double thisWidth = static_cast<ClassAlgorithm*>(this->drawingAlgorihtm)->getFullWidth(source);
	double thisHeight = static_cast<ClassAlgorithm*>(this->drawingAlgorihtm)->getFullHeight(source);
	double fullWidth = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
	double fullHeight = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);
	double thisRatio = thisWidth / thisHeight;
	double fullRatio = fullWidth / fullHeight;

	Ogre::Vector2 tmp = Ogre::Vector2(vecBeginLocal.x - vecEndLocal.x, vecBeginLocal.y - vecEndLocal.y);
	Ogre::Real angle = Ogre::Vector2(0, 1).angleTo(tmp).valueRadians();

	if (thisRatio <= fullRatio) {
		if (angle < Ogre::Math::PI) {
			x = thisWidth / 2;
		} else { x = - thisWidth / 2; }

		if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI) {
			y = thisHeight / 2 * thisRatio / fullRatio;
		} else { y = - thisHeight / 2 * thisRatio / fullRatio; }
	} else {
		if (angle < Ogre::Math::PI) {
			x = thisWidth / 2 * fullRatio / thisRatio;
		} else { x = - thisWidth / 2 * fullRatio / thisRatio; }

		if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI) {
			y = thisHeight / 2;
		} else { y = - thisHeight / 2; }
	}

	return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));*/
	return Ogre::Vector3(0,0,0);
}

Ogre::Vector3 ClassGraphics::getConnectorEndPoint(const std::string& A_name)
{
	/*Element* source = Utilities::getConnectorSource(connectorData);
	Element* target = Utilities::getConnectorTarget(connectorData);

	Ogre::SceneNode* beginNode = source->getGraphics()->getSceneNode();

	if (beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
		return ElementGraphics::getConnectorEndPoint(connectorData);

	double x = 0;
	double y = 0;

	Ogre::Vector3 vecBeginLocal = beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
	Ogre::Vector3 vecEndLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

	double thisWidth = static_cast<ClassAlgorithm*>(this->drawingAlgorihtm)->getFullWidth(target);
	double thisHeight = static_cast<ClassAlgorithm*>(this->drawingAlgorihtm)->getFullHeight(target);
	double fullWidth = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
	double fullHeight = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);
	double thisRatio = thisWidth / thisHeight;
	double fullRatio = fullWidth / fullHeight;

	Ogre::Vector2 tmp = Ogre::Vector2(vecEndLocal.x - vecBeginLocal.x, vecEndLocal.y - vecBeginLocal.y);
	Ogre::Real angle = Ogre::Vector2(0, 1).angleTo(tmp).valueRadians();

	if (thisRatio <= fullRatio) {
		if (angle < Ogre::Math::PI) {
			x = thisWidth / 2;
		} else { x = - thisWidth / 2; }

		if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI) {
			y = thisHeight / 2 * thisRatio / fullRatio;
		} else { y = - thisHeight / 2 * thisRatio / fullRatio; }
	} else {
		if (angle < Ogre::Math::PI) {
			x = thisWidth / 2 * fullRatio / thisRatio;
		} else { x = - thisWidth / 2 * fullRatio / thisRatio; }

		if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI) {
			y = thisHeight / 2;
		} else { y = - thisHeight / 2; }
	}

	return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));*/
	return Ogre::Vector3(0,0,0);
}
