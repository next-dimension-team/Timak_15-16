#include "JoinFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/JoinNode.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/JoinGraphics.h"
#include "../Container.h"
#include "Join.h"
#include "../../Core/Metamodel/include/JoinNode.h"


JoinFactory::JoinFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
    this->container = 0;
    this->centerPoint = 0;
}

JoinFactory::~JoinFactory()
{}

Element* JoinFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
    this->centerPoint = centerPoint;
    this->container = c;

    Join* elem = static_cast<Join*>(ElementFactory::factoryMethod());

    // TODO TEAM4
        //this->container->addElement(elem);

    return elem;
}

Element* JoinFactory::getElementInstance()
{
    return new Join();
}

std::string JoinFactory::getElementName()
{
    return "Join_";
}

std::string JoinFactory::getElementType()
{
    return Join::ELEMENT_TYPE;
}

Metamodel::Element* JoinFactory::getElementData()
{
    Metamodel::JoinNode* elemData = new Metamodel::JoinNode();

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

    return elemData;
}

ElementGraphics* JoinFactory::getElementGraphics(std::string name)
{
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::JoinNode::ELEMENT_TYPE);

    return new JoinGraphics(manualObject, sceneNode, drawingAlgorihtm);
}
