#include "ForkGraphics.h"

#include <OgreMath.h>
#include <OgrePrerequisites.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../Core/Element.h"
#include "../../Core/Utilities.h"
#include "ForkAlgorithm.h"


ForkGraphics::ForkGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm) : ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{}

ForkGraphics::~ForkGraphics()
{}

Ogre::Vector3 ForkGraphics::getConnectorBeginPoint(const std::string& A_name)
{
    Ogre::SceneNode* endNode = Utilities::getConnectorTarget(A_name)->getGraphics()->getSceneNode();

    if(endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
    {
        return ElementGraphics::getConnectorBeginPoint(A_name);
    }

    double x = 0;
    double y = 0;

    Ogre::Vector3 beginVector = node->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 endVector = endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double beginSize = static_cast<ForkAlgorithm*>(drawingAlgorihtm)->getFullSize();
    double connectWidth = Ogre::Math::Abs(node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double connectHeight = Ogre::Math::Abs(node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - endNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);

    Ogre::Real angle = Ogre::Vector2(endVector.x - beginVector.x, endVector.y - beginVector.y).angleTo(Ogre::Vector2(0, 1)).valueRadians();

    int a = 0;
    int b = 0;

    if(0 <= angle && angle < Ogre::Math::HALF_PI)
    {
        a = -1;
        b = 1;
    }
    else if(Ogre::Math::HALF_PI <= angle && angle < Ogre::Math::PI)
    {
        a = 1;
        b = 1;
        connectHeight *= -1;
    }
    else if(Ogre::Math::PI <= angle && angle < 8 * Ogre::Math::HALF_PI)
    {
        a = -1;
        b = -1;
    }
    else if(3 * Ogre::Math::HALF_PI <= angle && angle <= Ogre::Math::TWO_PI)
    {
        a = 1;
        b = -1;
        connectWidth *= -1;
    }

    double ratio = 0;
    if(Ogre::Math::Abs(connectWidth) < Ogre::Math::Abs(connectHeight))
    {
        ratio = connectWidth / connectHeight;
        x = - (b * ratio * beginSize / 2) / (a - ratio);
        y = - (b * beginSize / 2) / (a - ratio);
    }
    else
    {
        ratio = connectHeight / connectWidth;
        y = - (b * ratio * beginSize / 2) / (a * ratio -1);
        x = - (b * beginSize / 2) / (a * ratio - 1);
    }

    return node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}

Ogre::Vector3 ForkGraphics::getConnectorEndPoint(const std::string& A_name)
{
    Ogre::SceneNode* beginNode = Utilities::getConnectorSource(A_name)->getGraphics()->getSceneNode();

    if(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z != node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z)
    {
        return ElementGraphics::getConnectorBeginPoint(A_name);
    }

    double x = 0;
    double y = 0;

    Ogre::Vector3 beginVector = beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 endVector = node->convertLocalToWorldPosition(Ogre::Vector3::ZERO);

    double endSize = static_cast<ForkAlgorithm*>(drawingAlgorihtm)->getFullSize();
    double connectWidth = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x - node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).x);
    double connectHeight = Ogre::Math::Abs(beginNode->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y - node->convertLocalToWorldPosition(Ogre::Vector3::ZERO).y);

    Ogre::Real angle = Ogre::Vector2(beginVector.x - endVector.x, beginVector.y - endVector.y).angleTo(Ogre::Vector2(0, 1)).valueRadians();

    int a = 0;
    int b = 0;

    if(0 <= angle && angle < Ogre::Math::HALF_PI)
    {
        a = -1;
        b = 1;
    }
    else if(Ogre::Math::HALF_PI <= angle && angle < Ogre::Math::PI)
    {
        a = 1;
        b = 1;
        connectHeight *= -1;
    }
    else if(Ogre::Math::PI <= angle && angle < 3 * Ogre::Math::HALF_PI)
    {
        a = -1;
        b = -1;
    }
    else if(3 * Ogre::Math::HALF_PI <= angle && angle <= Ogre::Math::TWO_PI)
    {
        a = 1;
        b = -1;
        connectWidth *= -1;
    }

    double ratio = 0;
    if(Ogre::Math::Abs(connectWidth) < Ogre::Math::Abs(connectHeight))
    {
        ratio = connectWidth / connectHeight;
        x = - (b * ratio * endSize / 2) / (a - ratio);
        y = - (b * endSize / 2) / (a - ratio);
    }
    else
    {
        ratio = connectHeight / connectWidth;
        y = - (b * ratio * endSize / 2) / (a * ratio -1);
        x = - (b * endSize / 2) / (a * ratio - 1);
    }

    return node->convertLocalToWorldPosition(Ogre::Vector3(x, y, 0));
}
