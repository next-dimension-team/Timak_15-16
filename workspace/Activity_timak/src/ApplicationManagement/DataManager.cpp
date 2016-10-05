/*
 * DataManager.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "DataManager.h"


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

#include "../Core/Activity/ActivityFactory.h"
#include "../Core/Activity/DecisionFactory.h"
#include "../Core/Activity/MergeFactory.h"
#include "../Core/Activity/ForkFactory.h"
#include "../Core/Activity/JoinFactory.h"
#include "../Core/Activity/FinalNodeFactory.h"
#include "../Core/Activity/FlowFactory.h"
#include "../Core/Activity/Fragment.h"
#include "../Core/Activity/FragmentFactory.h"
#include "../Core/Activity/InitialNodeFactory.h"
#include "../Core/Aggregation.h"
#include "../Core/AggregationFactory.h"
#include "../Core/Association.h"
#include "../Core/AssociationFactory.h"
#include "../Core/Attribute.h"
#include "../Core/AttributeFactory.h"
#include "../Core/Class.h"
#include "../Core/ClassFactory.h"
#include "../Core/ContainerFactory.h"
#include "../Core/Generalisation.h"
#include "../Core/GeneralisationFactory.h"
#include "../Core/Layer.h"
#include "../Core/LayerBookmark.h"
#include "../Core/LayerBookmarkFactory.h"
#include "../Core/LayerFactory.h"
#include "../Core/Method.h"
#include "../Core/MethodFactory.h"
#include "../Core/Stereotype.h"
#include "../Core/StereotypeFactory.h"
#include "../DataStructure/Element.h"
#include "../DataStructure/Layer.h"
#include "../DataStructure/Space.h"
#include "DrawManager.h"
#include "ElementCollection.h"


#include "../HelperTeam4.h"

DataManager* DataManager::singletonObject = 0;


DataManager::DataManager()
{}

DataManager* DataManager::getInstance()
{
    if(DataManager::singletonObject == 0)
    {
        singletonObject = new DataManager();
        singletonObject->factories[	team4::DecisionNode::ELEMENT_TYPE] =		new DecisionFactory(DrawManager::getInstance());


        //singletonObject->factories[Association::ELEMENT_TYPE] =		new AssociationFactory(DrawManager::getInstance());
        //singletonObject->factories[Aggregation::ELEMENT_TYPE] =		new AggregationFactory(DrawManager::getInstance());
        //singletonObject->factories[Attribute::ELEMENT_TYPE] =		new AttributeFactory(DrawManager::getInstance());
        singletonObject->factories[Class::ELEMENT_TYPE] =			new ClassFactory(DrawManager::getInstance());
        //singletonObject->factories[Generalisation::ELEMENT_TYPE] =	new GeneralisationFactory(DrawManager::getInstance());

        //singletonObject->factories[Method::ELEMENT_TYPE] =			new MethodFactory(DrawManager::getInstance());
        //singletonObject->factories[Stereotype::ELEMENT_TYPE] =		new StereotypeFactory(DrawManager::getInstance());

        singletonObject->factories[ team4::ActivityNode::ELEMENT_TYPE] =		new ActivityFactory(DrawManager::getInstance());

        singletonObject->factories[	team4::MergeNode::ELEMENT_TYPE] =		    new MergeFactory(DrawManager::getInstance());
        singletonObject->factories[	team4::ForkNode::ELEMENT_TYPE] =		    new ForkFactory(DrawManager::getInstance());
        singletonObject->factories[	team4::JoinNode::ELEMENT_TYPE] =		    new JoinFactory(DrawManager::getInstance());

        singletonObject->factories[	team4::ActivityEdge::ELEMENT_TYPE] =			new FlowFactory(DrawManager::getInstance());
        singletonObject->factories[	team4::InitialNode::ELEMENT_TYPE] =		new InitialNodeFactory(DrawManager::getInstance());
        singletonObject->factories[	team4::FinalNode::ELEMENT_TYPE] =		new FinalNodeFactory(DrawManager::getInstance());
        singletonObject->factories[team4::StructuredActivityNode::ELEMENT_TYPE] =		new FragmentFactory(DrawManager::getInstance());
        singletonObject->factories[	Container::ELEMENT_TYPE] =		new ContainerFactory(DrawManager::getInstance());
        singletonObject->factories[Layer::ELEMENT_TYPE] =			new LayerFactory(DrawManager::getInstance());
        singletonObject->factories[LayerBookmark::ELEMENT_TYPE] =	new LayerBookmarkFactory(DrawManager::getInstance());
    }

    return singletonObject;
}


Layer* DataManager::createLayer()
{
    LayerFactory* factory = static_cast<LayerFactory*>(factories[Layer::ELEMENT_TYPE]);
    Layer* elem = static_cast<Layer*>(factory->factoryMethod());
    ElementCollection::getInstance()->insertElementTeam4(elem, Layer::ELEMENT_TYPE);
    //ElementCollection::getInstance()->insertElement(elem);
    ElementCollection::getInstance()->getSpace()->addLayer(dynamic_cast<Metamodel::Layer*>(elem->getData())); // TODO: make layer adding more sophisticated

    LayerBookmarkFactory* bookmarkFactory = static_cast<LayerBookmarkFactory*>(factories[LayerBookmark::ELEMENT_TYPE]);
    LayerBookmark* bookmarkElem = static_cast<LayerBookmark*>(bookmarkFactory->factoryMethod(elem));
    //ElementCollection::getInstance()->insertElement(bookmarkElem);
    ElementCollection::getInstance()->insertElementTeam4(bookmarkElem, LayerBookmark::ELEMENT_TYPE);
    // TODO: move somewhere? or remove totally? :)
    DrawManager::getInstance()->setBookmarksVisibility(false);
    ElementCollection::getInstance()->selectLayer(elem);
    return elem;
}

Class* DataManager::createClass(Layer* lay, std::string className, Ogre::Vector2* centerPoint)
{
    ClassFactory* factory = static_cast<ClassFactory*>(factories[Class::ELEMENT_TYPE]);
    Class* elem = static_cast<Class*>(factory->factoryMethod(lay, className, centerPoint));
    //ElementCollection::getInstance()->insertElement(elem);

    return elem;
}

void DataManager::createMethod(Class* cla, std::string methodName)
{
    MethodFactory* factory = static_cast<MethodFactory*>(factories[Method::ELEMENT_TYPE]);

    static_cast<Method*>(factory->factoryMethod(cla, methodName));
}

void DataManager::createAttribute(Class* cla, std::string attributeName)
{
    AttributeFactory* factory = static_cast<AttributeFactory*>(factories[Attribute::ELEMENT_TYPE]);
    static_cast<Attribute*>(factory->factoryMethod(cla, attributeName));
}

Association* DataManager::createAssociation(Class* source, Class* target)
{
    AssociationFactory* factory = static_cast<AssociationFactory*>(factories[Association::ELEMENT_TYPE]);
    Association* elem = static_cast<Association*>(factory->factoryMethod(source, target));
    return elem;
}

Generalisation* DataManager::createGeneralisation(Class* source, Class* target)
{
    GeneralisationFactory* factory = static_cast<GeneralisationFactory*>(factories[Generalisation::ELEMENT_TYPE]);
    Generalisation* elem = static_cast<Generalisation*>(factory->factoryMethod(source, target));
    return elem;
}

Aggregation* DataManager::createAggregation(Class* source, Class* target)
{
    AggregationFactory* factory = static_cast<AggregationFactory*>(factories[Aggregation::ELEMENT_TYPE]);
    Aggregation* elem = static_cast<Aggregation*>(factory->factoryMethod(source, target));
    return elem;
}

Stereotype* DataManager::setNewStereotype(Association* ass, std::string stereotypeName)
{
    // TODO: destructors!!
    StereotypeFactory* factory = static_cast<StereotypeFactory*>(factories[Stereotype::ELEMENT_TYPE]);
    Stereotype* elem = static_cast<Stereotype*>(factory->factoryMethod(ass, stereotypeName));
    //ElementCollection::getInstance()->insertElement(elem);
    return elem;
}

Stereotype* DataManager::setNewStereotype(Aggregation* agg, std::string stereotypeName)
{
    StereotypeFactory* factory = static_cast<StereotypeFactory*>(factories[Stereotype::ELEMENT_TYPE]);
    Stereotype* elem = static_cast<Stereotype*>(factory->factoryMethod(agg, stereotypeName));
    //ElementCollection::getInstance()->insertElement(elem);
    return elem;
}

Element* DataManager::createActivity(Container* c, std::string activityName, Ogre::Vector2* centerPoint)
{
    ActivityFactory* factory = static_cast<ActivityFactory*>(factories[team4::ActivityNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, activityName, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::ActivityNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;

}

Element* DataManager::createDecision(Container* c, Ogre::Vector2* centerPoint)
{
    DecisionFactory* factory = static_cast<DecisionFactory*>(factories[team4::DecisionNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::DecisionNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createMerge(Container* c, Ogre::Vector2* centerPoint)
{
    MergeFactory* factory = static_cast<MergeFactory*>(factories[team4::MergeNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::MergeNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createFork(Container* c, Ogre::Vector2* centerPoint)
{
    ForkFactory* factory = static_cast<ForkFactory*>(factories[team4::ForkNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::ForkNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createJoin(Container* c, Ogre::Vector2* centerPoint)
{
    JoinFactory* factory = static_cast<JoinFactory*>(factories[team4::JoinNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::ForkNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Container* DataManager::createContainer(Element* elemPar, Ogre::Vector2* centerPoint)
{
    ContainerFactory* factory = static_cast<ContainerFactory*>(factories[Container::ELEMENT_TYPE]);
    Container* elem = static_cast<Container*>(factory->factoryMethod(elemPar, centerPoint));
    ElementCollection::getInstance()->insertElementTeam4(elem, Container::ELEMENT_TYPE);
    return elem;
}

Element* DataManager::createFlow(const std::string& sourceName, const std::string& targetName, const std::string& A_text)
{
	DEF_BEGIN;
    std::pair<Element*, team4::MetamodelElement*> source = ElementCollection::getInstance()->findElement(sourceName);
    std::pair<Element*, team4::MetamodelElement*> target = ElementCollection::getInstance()->findElement(targetName);
    FlowFactory* factory = static_cast<FlowFactory*>(factories[team4::ActivityEdge::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(source, target));
    ElementCollection::getInstance()->insertElementTeam4(elem, team4::ActivityEdge::ELEMENT_TYPE, static_cast<team4::ActivityNode*>(source.second), static_cast<team4::ActivityNode*>(target.second), A_text);
    return elem;
    DEF_END;
}

Element* DataManager::createInitialNode(Container* c, Ogre::Vector2* centerPoint)
{
    InitialNodeFactory* factory = static_cast<InitialNodeFactory*>(factories[team4::InitialNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::InitialNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createFinalNode(Container* c, Ogre::Vector2* centerPoint)
{
    FinalNodeFactory* factory = static_cast<FinalNodeFactory*>(factories[team4::FinalNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::ForkNode::ELEMENT_TYPE);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createFragment(Container* c, Ogre::Vector2* centerPoint, int width, int height)
{
    //FragmentFactory* factory = static_cast<FragmentFactory*>(factories[Fragment::ELEMENT_TYPE]);
    FragmentFactory* factory = static_cast<FragmentFactory*>(factories[team4::StructuredActivityNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint,width,height));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::StructuredActivityNode::ELEMENT_TYPE);
     c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createLoop(Container* c, Ogre::Vector2* centerPoint, const std::string& A_init, const std::string& A_cond, int width, int height)
{
    FragmentFactory* factory = static_cast<FragmentFactory*>(factories[team4::StructuredActivityNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c, centerPoint,width,height));
    std::pair<Element*, team4::MetamodelElement*> element =ElementCollection::getInstance()->insertElementTeam4(elem, team4::LoopNode::ELEMENT_TYPE, A_init, A_cond);
    c->addElement(element);
    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

Element* DataManager::createAlt(Container* c, Ogre::Vector2* centerPoint, const std::vector<std::string>& A_condition, int width, int height)
{
    FragmentFactory* factory = static_cast<FragmentFactory*>(factories[team4::StructuredActivityNode::ELEMENT_TYPE]);
    Element* elem = static_cast<Element*>(factory->factoryMethod(c,centerPoint,width,height));
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->insertElementTeam4(elem, team4::ConditionNode::ELEMENT_TYPE, A_condition);
    c->addElement(element);

    elem->setCenter(centerPoint);
    elem->setLayer(DrawManager::getInstance()->getSelectedLayer()->getName());
    ElementCollection::getInstance()->insertElementToFragment(element.second->getName(),centerPoint);
    return elem;
}

void DataManager::resetFactories()
{
    static_cast<LayerFactory*>(factories[Layer::ELEMENT_TYPE])->resetMaxLayerLevel();
}

