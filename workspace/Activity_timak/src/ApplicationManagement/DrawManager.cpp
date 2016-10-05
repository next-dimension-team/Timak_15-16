/*
 * DrawManager.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "DrawManager.h"
#include "../HelperTeam4.h"
#include <OgreManualObject.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <iterator>
#include <vector>

#include "../Core/Activity/Activity.h"
#include "../Core/Activity/Decision.h"
#include "../Core/Activity/Merge.h"
#include "../Core/Activity/Fork.h"
#include "../Core/Activity/Join.h"
#include "../Core/Activity/FinalNode.h"
#include "../Core/Activity/Flow.h"
#include "../Core/Activity/Fragment.h"
#include "../Core/Activity/InitialNode.h"
#include "../Core/Aggregation.h"
#include "../Core/Class.h"
#include "../Core/Generalisation.h"
#include "../Core/LayerBookmark.h"
#include "../Core/Stereotype.h"
#include "../DataStructure/Association.h"
#include "../Graphics/Activity/ActivityAlgorithm.h"
#include "../Graphics/Activity/DecisionAlgorithm.h"
#include "../Graphics/Activity/MergeAlgorithm.h"
#include "../Graphics/Activity/ForkAlgorithm.h"
#include "../Graphics/Activity/JoinAlgorithm.h"
#include "../Graphics/Activity/FinalNodeAlgorithm.h"
#include "../Graphics/Activity/FlowAlgorithm.h"
#include "../Graphics/Activity/FragmentAlgorithm.h"
#include "../Graphics/Activity/InitialNodeAlgorithm.h"
#include "../Graphics/AggregationAlgorithm.h"
#include "../Graphics/AssociationAlgorithm.h"
#include "../Graphics/ClassAlgorithm.h"
#include "../Graphics/ContainerAlgorithm.h"
#include "../Graphics/ElementGraphics.h"
#include "../Graphics/GeneralisationAlgorithm.h"
#include "../Graphics/LayerAlgorithm.h"
#include "../Graphics/LayerBookmarkAlgorithm.h"
#include "../Graphics/StereotypeAlgorithm.h"
#include "ElementCollection.h"



#include "../Core/Metamodel/include/Action.h"
#include "../Core/Metamodel/include/Activity.h"
#include "../Core/Metamodel/include/ActivityEdge.h"
#include "../Core/Metamodel/include/ActivityFinalNode.h"
#include "../Core/Metamodel/include/ActivityGroup.h"
#include "../Core/Metamodel/include/ActivityNode.h"
#include "../Core/Metamodel/include/Alt.h"
#include "../Core/Metamodel/include/Behavior.h"
#include "../Core/Metamodel/include/Clause.h"
#include "../Core/Metamodel/include/CombinedFragment.h"
#include "../Core/Metamodel/include/ConditionNode.h"
#include "../Core/Metamodel/include/Constraint.h"
#include "../Core/Metamodel/include/ControlNode.h"
#include "../Core/Metamodel/include/DecisionNode.h"
#include "../Core/Metamodel/include/Element.h"
#include "../Core/Metamodel/include/ExecutableNode.h"
#include "../Core/Metamodel/include/FinalNode.h"
#include "../Core/Metamodel/include/FlowFinalNode.h"
#include "../Core/Metamodel/include/ForkNode.h"
#include "../Core/Metamodel/include/InitialNode.h"
#include "../Core/Metamodel/include/Interaction.h"
#include "../Core/Metamodel/include/InteractionFragment.h"
#include "../Core/Metamodel/include/InteractionOperand.h"
#include "../Core/Metamodel/include/InteractionOperator.h"
#include "../Core/Metamodel/include/JoinNode.h"
#include "../Core/Metamodel/include/Lifeline.h"
#include "../Core/Metamodel/include/LoopNode.h"
#include "../Core/Metamodel/include/MergeNode.h"
#include "../Core/Metamodel/include/ObjectNode.h"
#include "../Core/Metamodel/include/Opt.h"
#include "../Core/Metamodel/include/Par.h"
#include "../Core/Metamodel/include/SequenceNode.h"
#include "../Core/Metamodel/include/StructuredActivityNode.h"
#include "../Core/Metamodel/include/ValueSpecification.h"
#include "../Core/Metamodel/include/Variable.h"



#include "../Core/Metamodel/include/Element.h"

#include "MyGUI_Window.h"

#include "../Main.h"

DrawManager* DrawManager::singletonObject = 0;

DrawManager::DrawManager()
{
    this->sceneManager = 0;
    this->rootSceneNode = 0;
}

DrawManager::~DrawManager()
{}

DrawManager* DrawManager::getInstance()
{
    if (DrawManager::singletonObject == 0)
    {
        singletonObject = new DrawManager();

        singletonObject->algorithms[team4::ActivityNode::ELEMENT_TYPE] = new ActivityAlgorithm();
        singletonObject->algorithms[team4::DecisionNode::ELEMENT_TYPE] = new DecisionAlgorithm();
        singletonObject->algorithms[team4::MergeNode::ELEMENT_TYPE] = new MergeAlgorithm();
        singletonObject->algorithms[team4::ForkNode::ELEMENT_TYPE] = new ForkAlgorithm();
        singletonObject->algorithms[team4::JoinNode::ELEMENT_TYPE] = new JoinAlgorithm();
        singletonObject->algorithms[team4::FlowFinalNode::ELEMENT_TYPE] = new FlowAlgorithm();
        singletonObject->algorithms[team4::InitialNode::ELEMENT_TYPE] = new InitialNodeAlgorithm();
        singletonObject->algorithms[team4::FinalNode::ELEMENT_TYPE] = new FinalNodeAlgorithm();


        singletonObject->algorithms[Association::ELEMENT_TYPE] =   new AssociationAlgorithm();
        singletonObject->algorithms[Aggregation::ELEMENT_TYPE] =   new AggregationAlgorithm();
        singletonObject->algorithms[Class::ELEMENT_TYPE] = new ClassAlgorithm();
        singletonObject->algorithms[Generalisation::ELEMENT_TYPE] =  new GeneralisationAlgorithm();
        singletonObject->algorithms[Layer::ELEMENT_TYPE] = new LayerAlgorithm();
        singletonObject->algorithms[LayerBookmark::ELEMENT_TYPE] =  new LayerBookmarkAlgorithm();
        singletonObject->algorithms[Stereotype::ELEMENT_TYPE] = new StereotypeAlgorithm();
        singletonObject->algorithms[Container::ELEMENT_TYPE] = new ContainerAlgorithm();
        singletonObject->algorithms[Fragment::ELEMENT_TYPE] = new FragmentAlgorithm();
    }

    return singletonObject;
}

void DrawManager::init(Ogre::SceneManager* sceneManager)
{
    this->sceneManager = sceneManager;
    this->rootSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("mainNode");
}

void DrawManager::showLayers()
{
    std::vector<Layer*> layers = ElementCollection::getInstance()->getLayers();

    unsigned int i, j;
    for (i = 0; i < layers.size(); i++)
    {
        layers[i]->getGraphics()->getManualObject()->setVisible(true);

        std::vector<Class*> classes = layers[i]->getClasses();
        for (j = 0; j < classes.size(); j++)
        {
            classes[j]->getGraphics()->getManualObject()->setVisible(true);
        }
    }

    DrawManager::showConnectors();
}

Ogre::ManualObject* DrawManager::createManualObject(std::string name)
{
    return sceneManager->createManualObject(name);
}

Ogre::SceneNode* DrawManager::createChildSceneNode(std::string name, Ogre::Vector3 vector)
{
    return rootSceneNode->createChildSceneNode(name + "_node", vector);
}

DrawingAlgorithm* DrawManager::getDrawingAlgorithm(std::string name)
{
    return this->algorithms[name];
}

void DrawManager::setBookmarksVisibility(bool visible)
{
    unsigned int i;
    std::vector<LayerBookmark*> vector = ElementCollection::getInstance()->getLayerBookmarks();
    for (i = 0; i < vector.size(); i++)
    {
        vector[i]->getGraphics()->getManualObject()->setVisible(visible);
    }
}

void DrawManager::showConnectors()
{
    DEF_BEGIN;
    std::vector<std::pair<Element*, team4::MetamodelElement*>> connectors = ElementCollection::getInstance()->getConnectors();

    unsigned int i;
    for (i = 0; i < connectors.size(); i++)
    {
        connectors[i].first->getGraphics()->getSceneNode()->setVisible(true);
        // FIXME: check if this can be really removed
        //		connectors[i]->getGraphics()->getManualObject()->setVisible(true);
        //
        //		Metamodel::Association* a = dynamic_cast<Metamodel::Association*>(connectors[i]->getData());
        //		if (a != 0) {
        //			Stereotype* stereotype = static_cast<Stereotype*>(a->getStereotype());
        //			if (stereotype != 0) {
        //				stereotype->getGraphics()->getManualObject()->setVisible(true);
        //			}
        //		}
    }
}

void DrawManager::hideConnectorsExcept(Layer* layer)
{
    DEF_BEGIN;
    std::vector<std::pair<Element*, team4::MetamodelElement*>> connectors =  ElementCollection::getInstance()->getConnectors();

    for (unsigned int i = 0; i < connectors.size(); i++)
    {
        bool isOnLayer = true;

        /*Association* ass = dynamic_cast<Association*>(connectors[i]);
        if (ass != 0)
    {
            isOnLayer = ass->isOnLayer(layer);
    }

        Aggregation* agg = dynamic_cast<Aggregation*>(connectors[i]);
        if (agg != 0)
    {
            isOnLayer = agg->isOnLayer(layer);
    }

        Generalisation* gen = dynamic_cast<Generalisation*>(connectors[i]);
        if (gen != 0)
    {
            isOnLayer = gen->isOnLayer(layer);
    }

        Flow* flo = dynamic_cast<Flow*>(connectors[i]);
        if (flo != 0)
    {
            isOnLayer = flo->isOnLayer(layer);
    }*/

        if (!isOnLayer)
        {
            connectors[i].first->getGraphics()->getSceneNode()->setVisible(false);
            // FIXME: check if this can be really removed
            //			connectors[i]->getGraphics()->getManualObject()->setVisible(false);
            //
            //			Metamodel::Association* ad = dynamic_cast<Metamodel::Association*>(connectors[i]->getData());
            //			if (ad != 0) {
            //				Stereotype* stereotype = static_cast<Stereotype*>(ad->getStereotype()->getWrapper());
            //				if (stereotype != 0) {
            //					stereotype->getGraphics()->getManualObject()->setVisible(false);
            //				}
            //			}
        }
    }
}

void DrawManager::hideLayersExcept(Layer* layer)
{
    DEF_BEGIN;
    // TODO TEAM4
    /*std::vector<Layer*> layers = ElementCollection::getInstance()->getLayers();

       unsigned int i, j;
       for (i = 0; i < layers.size(); i++)
       {
           if (layers[i]->getName().compare(layer->getName()) != 0)
           {
               layers[i]->getGraphics()->getManualObject()->setVisible(false);

               std::vector<Class*> classes = layers[i]->getClasses();
               for (j = 0; j < classes.size(); j++)
               {
                   classes[j]->getGraphics()->getManualObject()->setVisible(false);
               }
           }
       }

       DrawManager::hideConnectorsExcept(layer);*/
}

void DrawManager::drawAll()
{
	DEF_BEGIN;
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elements = ElementCollection::getInstance()->getAllElements();

   /* std::cout << "size " << elements.size() << std::endl;
    for (auto i : elements)
    {
        std::cout << i.second->getName() << std::endl;
    }*/

    for (auto i : elements)
    {
        //std::cout << "\n1.  "  << i.second->getName() << std::endl;
        if (i.first !=NULL && !i.first->drawing)
        {
            std::cout << "2. " << i.second->getName() << std::endl;
            i.first->draw(i.second->getName());
            //std::cout << "3." << std::endl;
            i.first->drawing = true;
        }
    }
    //DEF_END;
}

void DrawManager::select(const std::string &A_name)
{
    std::pair<Element*, team4::MetamodelElement*> elements = ElementCollection::getInstance()->findElement(A_name);
    elements.first->select();
}

void DrawManager::unselect(const std::string &A_name)
{
    std::pair<Element*, team4::MetamodelElement*> elements = ElementCollection::getInstance()->findElement(A_name);
    elements.first->unselected();
}



Layer* DrawManager::getSelectedLayer(){
	return ElementCollection::getInstance()->getSelectedLayer();
}
void DrawManager::DrawSelectedLayers()
{
	ElementCollection::getInstance()->setSelectedLayers();
}

void DrawManager::DrawNormalLayers()
{
	ElementCollection::getInstance()->setNormalLayers();
}

void DrawManager::IncrementLayer()
{
	ElementCollection::getInstance()->IncrementLayer();
}

void DrawManager::DecrementLayer()
{
	ElementCollection::getInstance()->DecrementLayer();
}
void DrawManager::DestroyAllAttachedMovableObjects(Ogre::SceneNode* node)
{
    if (!node)
        return;

    // Destroy all the attached objects
    Ogre::SceneNode::ObjectIterator itObject =
        node->getAttachedObjectIterator();

    while (itObject.hasMoreElements())
        node->getCreator()->destroyMovableObject(itObject.getNext());

    // Recurse to child SceneNodes
    Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

    while (itChild.hasMoreElements())
    {
        Ogre::SceneNode* pChildNode =
            static_cast<Ogre::SceneNode*>(itChild.getNext());
        DestroyAllAttachedMovableObjects(pChildNode);
    }
}

void DrawManager::destroySceneNode(Ogre::SceneNode* node)
{
    if (!node)
        return;
    DestroyAllAttachedMovableObjects(node);
    node->removeAndDestroyAllChildren();
    node->getCreator()->destroySceneNode(node);
}

// TODO: not finished
void DrawManager::showContainers(Container* container) // TODO: rename
{
	std::vector<std::pair<Element*, team4::MetamodelElement*>> elements = container->getElements();

    unsigned int i;
    for (i = 0; i < elements.size(); i++)
    {
        elements[i].first->getGraphics()->getManualObject()->setVisible(true);

        Container* childContainer = dynamic_cast<Container*>(elements[i].first);
        if (childContainer)
        {
            showContainers(childContainer);
        }
    }
}

// TODO: not finished
void DrawManager::setVisibilityAll(bool visible)
{
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elements = ElementCollection::getInstance()->getAllElements();

    for (auto i: elements)
    {
        i.first->getGraphics()->getManualObject()->setVisible(visible);
    }
}

void DrawManager::cleanUp()
{
    ActivityAlgorithm::cleanUp();
    ClassAlgorithm::cleanUp();
    FragmentAlgorithm::cleanUp();
    StereotypeAlgorithm::cleanUp();
}

void DrawManager::redrawConnectors()
{
    std::vector<std::pair<Element*, team4::MetamodelElement*>> connectors =  ElementCollection::getInstance()->getConnectors();

    for (unsigned int i = 0; i < connectors.size(); i++)
    {
        Element* e = connectors[i].first;

        Ogre::ManualObject* mo = e->getGraphics()->getManualObject();
        mo->detachFromParent();
        mo->clear();

        Ogre::SceneNode* sn = e->getGraphics()->getSceneNode();
        sn->resetToInitialState();

        e->draw(connectors[i].second->getName());
    }
}
