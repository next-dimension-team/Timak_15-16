/*
 * ContainerGraphics.cpp
 *
 *  Created on: 14.10.2013
 *      Author: Schade
 */

#include "ContainerGraphics.h"

#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../Core/Utilities.h"
#include "../HelperTeam4.h"


ContainerGraphics::ContainerGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm, int width, int height)
        : ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{
    this->width = width;
    this->height = height;
}

ContainerGraphics::~ContainerGraphics()
{}


void ContainerGraphics::setSize(int width, int height)
{
    this->width =	width;
    this->height =	height;
}

int ContainerGraphics::getWidth()
{
    return this->width;
}

int ContainerGraphics::getHeight()
{
    return this->height;
}

Ogre::Vector3 ContainerGraphics::getConnectorBeginPoint(const std::string& A_name)
{
	DEF_BEGIN;
    Ogre::SceneNode* endNode = Utilities::getConnectorTargetSceneNode(A_name);

    if (endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorBeginPoint(A_name);

    double x = 0;
    double y = 0;

    Ogre::Vector3 vecBeginLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double thisWidth = this->getWidth();
    double thisHeight = this->getHeight();

    double fullWidth = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double fullHeight = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);
    double thisRatio = thisWidth / thisHeight;
    double fullRatio = fullWidth / fullHeight;

    Ogre::Vector2 tmp = Ogre::Vector2(vecBeginLocal.x - vecEndLocal.x, vecBeginLocal.y - vecEndLocal.y);
    Ogre::Real angle = Ogre::Vector2(0, 1).angleTo(tmp).valueRadians();

    if (thisRatio <= fullRatio)
    {
        if (angle < Ogre::Math::PI)
        {
            x = thisWidth / 2;
        }
        else
        {
            x = - thisWidth / 2;
        }

        if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI)
        {
            y = thisHeight / 2 * thisRatio / fullRatio;
        }
        else
        {
            y = - thisHeight / 2 * thisRatio / fullRatio;
        }
    }
    else
    {
        if (angle < Ogre::Math::PI)
        {
            x = thisWidth / 2 * fullRatio / thisRatio;
        }
        else
        {
            x = - thisWidth / 2 * fullRatio / thisRatio;
        }

        if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI)
        {
            y = thisHeight / 2;
        }
        else
        {
            y = - thisHeight / 2;
        }
    }

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}

Ogre::Vector3 ContainerGraphics::getConnectorEndPoint(const std::string& A_name)
{
    Ogre::SceneNode* beginNode = Utilities::getConnectorSourceSceneNode(A_name);

    if (beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorEndPoint(A_name);

    double x = 0;
    double y = 0;

    Ogre::Vector3 vecBeginLocal = beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double thisWidth = this->getWidth();
    double thisHeight = this->getHeight();

    double fullWidth = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double fullHeight = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);
    double thisRatio = thisWidth / thisHeight;
    double fullRatio = fullWidth / fullHeight;

    Ogre::Vector2 tmp = Ogre::Vector2(vecEndLocal.x - vecBeginLocal.x, vecEndLocal.y - vecBeginLocal.y);
    Ogre::Real angle = Ogre::Vector2(0, 1).angleTo(tmp).valueRadians();

    if (thisRatio <= fullRatio)
    {
        if (angle < Ogre::Math::PI)
        {
            x = thisWidth / 2;
        }
        else
        {
            x = - thisWidth / 2;
        }

        if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI)
        {
            y = thisHeight / 2 * thisRatio / fullRatio;
        }
        else
        {
            y = - thisHeight / 2 * thisRatio / fullRatio;
        }
    }
    else
    {
        if (angle < Ogre::Math::PI)
        {
            x = thisWidth / 2 * fullRatio / thisRatio;
        }
        else
        {
            x = - thisWidth / 2 * fullRatio / thisRatio;
        }

        if (angle < 1.5 * Ogre::Math::PI && angle > 0.5 * Ogre::Math::PI)
        {
            y = thisHeight / 2;
        }
        else
        {
            y = - thisHeight / 2;
        }
    }

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}
