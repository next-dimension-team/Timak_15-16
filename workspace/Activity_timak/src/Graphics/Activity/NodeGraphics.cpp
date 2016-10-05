/*
 * NodeGraphics.cpp
 *
 *  Created on: 21.10.2013
 *      Author: Schade
 */

#include "NodeGraphics.h"

#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <typeinfo>

#include "../../Core/Element.h"
#include "../../Core/Utilities.h"
//#include "../DrawingAlgorithm.h"
#include "FinalNodeAlgorithm.h"
#include "InitialNodeAlgorithm.h"


NodeGraphics::NodeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
        : ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{}

NodeGraphics::~NodeGraphics()
{}

Ogre::Vector3 NodeGraphics::getConnectorBeginPoint(const std::string& A_name)
{
    DEF_BEGIN;
    Element* target = Utilities::getConnectorTarget(A_name);

    Ogre::SceneNode* endNode = target->getGraphics()->getSceneNode();

    if (endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorBeginPoint(A_name);

    Ogre::Vector3 vecBeginLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    Ogre::Vector2 tmp = Ogre::Vector2(vecEndLocal.x - vecBeginLocal.x, vecEndLocal.y - vecBeginLocal.y);
    Ogre::Real angle = Ogre::Vector2(1, 0).angleTo(tmp).valueRadians();

    // TODO: VERY ugly!! - use polymorphism instead of this !@#$%
    double thisSize = 0;
    if (typeid(InitialNodeAlgorithm) == typeid(*this->drawingAlgorihtm))
    {
        thisSize = static_cast<InitialNodeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    }
    else if (typeid(FinalNodeAlgorithm) == typeid(*this->drawingAlgorihtm))
    {
        thisSize = static_cast<FinalNodeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    }

    double x = thisSize / 2 * Ogre::Math::Cos(angle, false);
    double y = thisSize / 2 * Ogre::Math::Sin(angle, false);

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}

Ogre::Vector3 NodeGraphics::getConnectorEndPoint(const std::string& A_name)
{
    Element* source = Utilities::getConnectorSource(A_name);

    Ogre::SceneNode* beginNode = source->getGraphics()->getSceneNode();

    if (beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorBeginPoint(A_name);

    Ogre::Vector3 vecBeginLocal = beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    Ogre::Vector2 tmp = Ogre::Vector2(vecBeginLocal.x - vecEndLocal.x, vecBeginLocal.y - vecEndLocal.y);
    Ogre::Real angle = Ogre::Vector2(1, 0).angleTo(tmp).valueRadians();

    // TODO: VERY ugly!! - use polymorphism instead of this !@#$%
    double thisSize = 0;
    if (typeid(InitialNodeAlgorithm) == typeid(*this->drawingAlgorihtm))
    {
        thisSize = static_cast<InitialNodeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    }
    else if (typeid(FinalNodeAlgorithm) == typeid(*this->drawingAlgorihtm))
    {
        thisSize = static_cast<FinalNodeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    }

    double x = thisSize / 2 * Ogre::Math::Cos(angle, false);
    double y = thisSize / 2 * Ogre::Math::Sin(angle, false);

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}
