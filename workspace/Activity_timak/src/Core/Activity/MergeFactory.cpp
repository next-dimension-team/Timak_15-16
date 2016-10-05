#include "MergeFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>

#include "../../ApplicationManagement/DrawManager.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../../DataStructure/MergeNode.h"
#include "../../DataStructure/Layer.h"
#include "../../Graphics/Activity/MergeGraphics.h"
#include "../Container.h"
#include "Merge.h"
#include "../../Core/Metamodel/include/MergeNode.h"

MergeFactory::MergeFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
    this->container = 0;
    this->centerPoint = 0;
}

MergeFactory::~MergeFactory()
{}

Element* MergeFactory::factoryMethod(Container* c, Ogre::Vector2* centerPoint)
{
    this->centerPoint = centerPoint;
    this->container = c;

    Merge* elem = static_cast<Merge*>(ElementFactory::factoryMethod());

    // TODO TEAM4
        //this->container->addElement(elem);

    return elem;
}

Element* MergeFactory::getElementInstance()
{
    return new Merge();
}

std::string MergeFactory::getElementName()
{
    return "Merge_";
}

std::string MergeFactory::getElementType()
{
    return Merge::ELEMENT_TYPE;
}

Metamodel::Element* MergeFactory::getElementData()
{
    Metamodel::MergeNode* elemData = new Metamodel::MergeNode();

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

ElementGraphics* MergeFactory::getElementGraphics(std::string name)
{
    Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
    Ogre::SceneNode* sceneNode = this->container->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *new Ogre::Vector3(centerPoint->x, centerPoint->y, 0));
    DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(team4::MergeNode::ELEMENT_TYPE);

    return new MergeGraphics(manualObject, sceneNode, drawingAlgorihtm);
}
