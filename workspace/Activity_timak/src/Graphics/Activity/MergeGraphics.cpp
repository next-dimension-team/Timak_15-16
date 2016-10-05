#include "MergeGraphics.h"

#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../Core/Element.h"
#include "../../Core/Utilities.h"
#include "MergeAlgorithm.h"

MergeGraphics::MergeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
        : ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{}

MergeGraphics::~MergeGraphics()
{}

Ogre::Vector3 MergeGraphics::getConnectorBeginPoint(const std::string& A_name)
{
	DEF_BEGIN;
    Element* target = Utilities::getConnectorTarget(A_name);

    Ogre::SceneNode* endNode = target->getGraphics()->getSceneNode();

    if (endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorBeginPoint(A_name);

    double x = 0;
    double y = 0;

    Ogre::Vector3 vecBeginLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double thisSize = static_cast<MergeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    double fullWidth = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double fullHeight = Ogre::Math::Abs(this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);

    Ogre::Vector2 tmp = Ogre::Vector2(vecEndLocal.x - vecBeginLocal.x, vecEndLocal.y - vecBeginLocal.y);
    Ogre::Real angle = tmp.angleTo(Ogre::Vector2(0, 1)).valueRadians();

    int a = 0;
    int b = 0;

    if (0 <= angle && angle < Ogre::Math::HALF_PI)
    {
        a = -1;
        b = 1;
    }
    else if (Ogre::Math::HALF_PI <= angle && angle < Ogre::Math::PI)
    {
        a = 1;
        b = 1;
        fullHeight *= -1;
    }
    else if (Ogre::Math::PI <= angle && angle < 3 * Ogre::Math::HALF_PI)
    {
        a = -1;
        b = -1;
    }
    else if (3 * Ogre::Math::HALF_PI <= angle && angle <= Ogre::Math::TWO_PI)
    {
        a = 1;
        b = -1;
        fullWidth *= -1;
    }

    double ratio = 0;
    if (Ogre::Math::Abs(fullWidth) < Ogre::Math::Abs(fullHeight))
    {
        ratio = fullWidth / fullHeight;
        x = - (b * ratio * thisSize / 2) / (a - ratio);
        y = - (b * thisSize / 2) / (a - ratio);
    }
    else
    {
        ratio = fullHeight / fullWidth;
        y = - (b * ratio * thisSize / 2) / (a * ratio -1);
        x = - (b * thisSize / 2) / (a * ratio - 1);
    }

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}

Ogre::Vector3 MergeGraphics::getConnectorEndPoint(const std::string& A_name)
{
    Element* source = Utilities::getConnectorSource(A_name);

    Ogre::SceneNode* beginNode = source->getGraphics()->getSceneNode();

    if (beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
        return ElementGraphics::getConnectorBeginPoint(A_name);

    double x = 0;
    double y = 0;

    Ogre::Vector3 vecBeginLocal = beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 vecEndLocal = getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double thisSize = static_cast<MergeAlgorithm*>(this->drawingAlgorihtm)->getFullSize();
    double fullWidth = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double fullHeight = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - this->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);

    Ogre::Vector2 tmp = Ogre::Vector2(vecBeginLocal.x - vecEndLocal.x, vecBeginLocal.y - vecEndLocal.y);
    Ogre::Real angle = tmp.angleTo(Ogre::Vector2(0, 1)).valueRadians();

    int a = 0;
    int b = 0;

    if (0 <= angle && angle < Ogre::Math::HALF_PI)
    {
        a = -1;
        b = 1;
    }
    else if (Ogre::Math::HALF_PI <= angle && angle < Ogre::Math::PI)
    {
        a = 1;
        b = 1;
        fullHeight *= -1;
    }
    else if (Ogre::Math::PI <= angle && angle < 3 * Ogre::Math::HALF_PI)
    {
        a = -1;
        b = -1;
    }
    else if (3 * Ogre::Math::HALF_PI <= angle && angle <= Ogre::Math::TWO_PI)
    {
        a = 1;
        b = -1;
        fullWidth *= -1;
    }

    double ratio = 0;
    if (Ogre::Math::Abs(fullWidth) < Ogre::Math::Abs(fullHeight))
    {
        ratio = fullWidth / fullHeight;
        x = - (b * ratio * thisSize / 2) / (a - ratio);
        y = - (b * thisSize / 2) / (a - ratio);
    }
    else
    {
        ratio = fullHeight / fullWidth;
        y = - (b * ratio * thisSize / 2) / (a * ratio -1);
        x = - (b * thisSize / 2) / (a * ratio - 1);
    }

    return this->node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}
