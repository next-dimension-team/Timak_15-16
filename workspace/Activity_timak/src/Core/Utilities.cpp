/*
 * Utilities.cpp
 */

#include "Utilities.h"

#include "../ApplicationManagement/ElementCollection.h"
#include "../DataStructure/ActivityNode.h"
#include "../DataStructure/Association.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/ControlFlow.h"
#include "../DataStructure/Generalization.h"
#include "../DataStructure/Property.h"
#include "../Graphics/ElementGraphics.h"
#include "Element.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"
#include "../Core/Metamodel/include/ActivityEdge.h"
#include "../Core/Metamodel/include/ActivityNode.h"
#include "../HelperTeam4.h"


Ogre::SceneNode* Utilities::getSceneNode(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    return element.first->getGraphics()->getSceneNode();
}

Ogre::SceneNode* Utilities::getConnectorSourceSceneNode(const std::string& A_name)
{
    Element* e = Utilities::getConnectorSource(A_name);
    return (e == 0) ? 0 : e->getGraphics()->getSceneNode();
}

Ogre::SceneNode* Utilities::getConnectorTargetSceneNode(const std::string& A_name)
{
    Element* e = Utilities::getConnectorTarget(A_name);
    return (e == 0) ? 0 : e->getGraphics()->getSceneNode();
}



Element* Utilities::getConnectorSource(const std::string& A_name)
{
	DEF_BEGIN;
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);

    DEF_LOG(element.second->getType());

    if (element.second->getType() == team4::ActivityEdge::ELEMENT_TYPE)
    {
        std::pair<Element*, team4::MetamodelElement*> source = ElementCollection::getInstance()->findElement(static_cast<team4::ActivityEdge*>(element.second)->source->getName());
        DEF_LOG(source.second->getName());
        return source.first;
    }
    DEFL;
    return 0;
}

Element* Utilities::getConnectorTarget(const std::string& A_name)
{
	DEF_BEGIN;
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    DEF_LOG(element.second->getType());

    if (element.second->getType() == team4::ActivityEdge::ELEMENT_TYPE)
    {
        std::pair<Element*, team4::MetamodelElement*> target = ElementCollection::getInstance()->findElement(static_cast<team4::ActivityEdge*>(element.second)->target->getName());
        DEF_LOG(target.second->getName());
        return target.first;
    }
    DEFL;
    return 0;
}







Element* Utilities::getConnectorSource(Metamodel::Element* connectorData)
{
    // This can be not efficient and maybe optimization will be needed in the future
    // Before optimization look at: http://en.wikipedia.org/wiki/Program_optimization#Quotes

    Metamodel::Association* ad = dynamic_cast<Metamodel::Association*>(connectorData);
    if (ad != 0)
    {
        return ElementCollection::getInstance()->findElement((ad->getMemberEnds()[0])->getClass());
    }

    Metamodel::Generalization* gd = dynamic_cast<Metamodel::Generalization*>(connectorData);
    if (gd != 0)
    {
        return ElementCollection::getInstance()->findElement(gd->getSpecific());
    }

    Metamodel::ControlFlow* cfd = dynamic_cast<Metamodel::ControlFlow*>(connectorData);
    if (cfd != 0)
    {
        return ElementCollection::getInstance()->findElement(cfd->getSource());
    }

    return 0;
}

Element* Utilities::getConnectorTarget(Metamodel::Element* connectorData)
{
    // This can be not efficient and maybe optimization will be needed in the future
    // Before optimization look at: http://en.wikipedia.org/wiki/Program_optimization#Quotes

    Metamodel::Association* ad = dynamic_cast<Metamodel::Association*>(connectorData);
    if (ad != 0)
    {
        return ElementCollection::getInstance()->findElement((ad->getMemberEnds()[1])->getClass());
    }

    Metamodel::Generalization* gd = dynamic_cast<Metamodel::Generalization*>(connectorData);
    if (gd != 0)
    {
        return ElementCollection::getInstance()->findElement(gd->getGeneral());
    }

    Metamodel::ControlFlow* cfd = dynamic_cast<Metamodel::ControlFlow*>(connectorData);
    if (cfd != 0)
    {
        return ElementCollection::getInstance()->findElement(cfd->getTarget());
    }

    return 0;
}

Ogre::SceneNode* Utilities::getConnectorSourceSceneNode(Metamodel::Element* connectorData)
{
    Element* e = Utilities::getConnectorSource(connectorData);
    return (e == 0) ? 0 : e->getGraphics()->getSceneNode();
}

Ogre::SceneNode* Utilities::getConnectorTargetSceneNode(Metamodel::Element* connectorData)
{
    Element* e = Utilities::getConnectorTarget(connectorData);
    return (e == 0) ? 0 : e->getGraphics()->getSceneNode();
}

Ogre::SceneNode* Utilities::getSceneNode(Metamodel::Element* ed)
{
    return ElementCollection::getInstance()->findElement(ed)->getGraphics()->getSceneNode();
}



