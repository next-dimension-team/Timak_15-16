/*
 * ElementCollection.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "ElementCollection.h"

#include <OgreManualObject.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <iterator>
#include <stdexcept>
#include <utility>

#include "../Core/Class.h"
#include "../DataStructure/Space.h"
#include "../Graphics/ElementGraphics.h"
#include "../Main.h"
#include "../HelperTeam4.h"

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


#include "../Graphics/Activity/FragmentAlgorithm.h"
#include "../Graphics/Activity/FragmentGraphics.h"
#include "../Core/Activity/Fragment.h"
#include "../Core/Activity/FragmentFactory.h"

#include "Metamodel.h"
#include "ControlerMetamodel.h"
#include "DrawManager.h"
typedef std::map<std::string, std::pair<Element* ,int>>::iterator it_type;

ElementCollection* ElementCollection::singletonObject = 0;


ElementCollection* ElementCollection::getInstance()
{
    if (ElementCollection::singletonObject == 0)
    {
        singletonObject = new ElementCollection();
    }

    return singletonObject;
}

ElementCollection::ElementCollection()
{
    this->space = 0;
    _metamodel = new team4::MetaModel();
    _controlerMetamodel = new team4::ControlerMetamodel(*_metamodel);
}

ElementCollection::~ElementCollection()
{}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::findElement(const std::string& A_name)
{
    std::map<std::string, std::pair<Element* ,int>>::const_iterator p;
    // find value given key
    p = this->elements1.find(A_name);
    if(p == this->elements1.end())
    {
        std::cout << "Key not in map.\n";
        return std::pair<Element*, team4::MetamodelElement*>(NULL, NULL);
    }
    return std::make_pair(p->second.first, _controlerMetamodel->get(p->second.second));
}

Element* ElementCollection::findElement(Metamodel::Element* searched)
{
    /*for(std::map<std::string, Element*>::const_iterator i = elements1.begin(); i != elements1.end(); i++)
{
        Metamodel::Element* compared = i->second->getData();
        if (compared == searched)
        {
            return i->second;
        }
}*/
    return 0;
}

Layer* ElementCollection::findLayerOfClass(Class* cla)
{
    std::vector<Layer*> layers = ElementCollection::getLayers();

    for(std::vector<Layer*>::iterator layerIterator = layers.begin(); layerIterator != layers.end(); layerIterator++)
    {
        Class* foundClass = (*layerIterator)->findClass(cla->getName());
        if (foundClass != 0)
        {
            return *layerIterator;
        }
    }

    return 0;
}

Layer* ElementCollection::findLayerOfElement(Element* elem)
{
    Container* container = findContainerOfElement(elem);

    if (container)
    {
        Layer* layer = dynamic_cast<Layer*>(container);
        if (layer)
        {
            return layer;
        }
        else
        {
            return this->findLayerOfElement(container);
        }
    }

    return 0;
}

Container* ElementCollection::findContainerOfElement(Element* elem)
{
    /* for(std::map<std::map<std::string, std::pair<Element* ,int>>::iterator i = elements1.begin(); i != elements1.end(); i++)
     {
         Container* container = dynamic_cast<Container*>(i->second.first);
         if (container)
         {
             if (container->findElement(elem->getName()))
             {
                 return container;
             }
         }
     }*/

    return 0;
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::insertElementTeam4(Element * elem, const std::string &A_type,	const std::string&  A_init, const std::string& A_cond)
{
    if (elem == 0)
    {
        throw new std::invalid_argument("Cannot insert 0.");
    }
    if (space == 0)
    {
        space = new Metamodel::Space();
    }
    team4::MetamodelElement* metamodelElement = _controlerMetamodel->add(A_type, A_init, A_cond);
    elements1.insert( std::pair<std::string, std::pair<Element* ,int>>( metamodelElement->getName(), std::pair<Element* ,int>(elem, metamodelElement->getId())));
    return std::pair<Element*, team4::MetamodelElement*>(elem, metamodelElement);
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::insertElementTeam4(Element * elem, const std::string &A_type, const std::vector<std::string>& A_condition)
{
    if (elem == 0)
    {
        throw new std::invalid_argument("Cannot insert 0.");
    }
    if (space == 0)
    {
        space = new Metamodel::Space();
    }
    team4::MetamodelElement* metamodelElement = _controlerMetamodel->add(A_type, A_condition);
    elements1.insert( std::pair<std::string, std::pair<Element* ,int>>( metamodelElement->getName(), std::pair<Element* ,int>(elem, metamodelElement->getId())));
    return std::pair<Element*, team4::MetamodelElement*>(elem, metamodelElement);
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::insertElementTeam4(Element * elem, const std::string &A_type)
{
    if (elem == 0)
    {
        throw new std::invalid_argument("Cannot insert 0.");
    }
    if (space == 0)
    {
        space = new Metamodel::Space();
    }
    team4::MetamodelElement* metamodelElement = _controlerMetamodel->add(A_type);
    elements1.insert( std::pair<std::string, std::pair<Element* ,int>>( metamodelElement->getName(), std::pair<Element* ,int>(elem, metamodelElement->getId())));
    return std::pair<Element*, team4::MetamodelElement*>(elem, metamodelElement);
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::insertElementTeam4(Element * elem, const std::string &A_type, team4::ActivityNode *A_source, team4::ActivityNode *A_target, const std::string& A_text)
{
    if (elem == 0)
    {
        throw new std::invalid_argument("Cannot insert 0.");
    }
    if (space == 0)
    {
        space = new Metamodel::Space();
    }
    team4::MetamodelElement* metamodelElement = _controlerMetamodel->add(A_type, A_source, A_target, A_text);
    elements1.insert( std::pair<std::string, std::pair<Element* ,int>>( metamodelElement->getName(), std::pair<Element* ,int>(elem, metamodelElement->getId())));
    return std::pair<Element*, team4::MetamodelElement*>(elem, metamodelElement);
}

void ElementCollection::insertElementToFragment(const std::string &A_name, Ogre::Vector2* centerPoint)
{
	  std::pair<Element*, team4::MetamodelElement*> element = searchCloseFragment(centerPoint);
	  if(element.second != NULL && element.second->getName() != A_name) {
		  if (element.second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) == 0){
			  static_cast<team4::ConditionNode*>(element.second)->cluase.front()->elements.push_back(A_name);
		/*for (auto i:static_cast<team4::ConditionNode*>(element.second)->cluase.front()->elements)
							std::cout<<"in fragment alt" <<i<<std::endl;*/
		  }
		  if (element.second->getType().compare(team4::LoopNode::ELEMENT_TYPE) == 0) {
			  static_cast<team4::LoopNode*>(element.second)->elements.push_back(A_name);
		/*for (auto i:static_cast<team4::LoopNode*>(element.second)->elements)
			std::cout<<"in fragment loop" <<i<<std::endl;*/
		  }
		  if (element.second->getType().compare(team4::StructuredActivityNode::ELEMENT_TYPE) == 0) {
			  static_cast<team4::StructuredActivityNode*>(element.second)->elements.push_back(A_name);
		/*for (auto i:static_cast<team4::StructuredActivityNode*>(element.second)->elements)
					std::cout<<"in fragment seq"<<i<<std::endl;*/
		  }
	 }
}
// TODO: experimental!!
void ElementCollection::removeElement(const std::string& A_Name)
{
    std::pair<Element*, team4::MetamodelElement*> elem = findElement(A_Name);
    if (elem.second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) == 0) {
    	for (auto i:static_cast<team4::ConditionNode*>(elem.second)->cluase) {
    		for (auto j:i->elements) {
    			std::pair<Element*, team4::MetamodelElement*> element = findElement(j);
    			if (element.first != NULL) {
    				this->elements1.erase(j);
    				element.first->getGraphics()->getSceneNode()->detachObject(elem.first->getGraphics()->getManualObject());
    				Main::sMSceneMgr->destroyManualObject(element.first->getGraphics()->getManualObject());
    				Main::sMSceneMgr->destroySceneNode(element.first->getGraphics()->getSceneNode());
    			}
    		}
    	}

    }
    else if (elem.second->getType().compare(team4::LoopNode::ELEMENT_TYPE) == 0 ){
    	for (auto i:static_cast<team4::LoopNode*>(elem.second)->elements) {
    	    			std::pair<Element*, team4::MetamodelElement*> element = findElement(i);
    	    			if (element.first != NULL) {
    	    				this->elements1.erase(i);
    	    				element.first->getGraphics()->getSceneNode()->detachObject(elem.first->getGraphics()->getManualObject());
    	    				Main::sMSceneMgr->destroyManualObject(element.first->getGraphics()->getManualObject());
    	    				Main::sMSceneMgr->destroySceneNode(element.first->getGraphics()->getSceneNode());
    	    			}
    	    		}
    }
    else if( elem.second->getType().compare(team4::StructuredActivityNode::ELEMENT_TYPE) == 0){
    	for (auto i:static_cast<team4::StructuredActivityNode*>(elem.second)->elements) {
    				std::cout<<"mazem_veci1 "<<i<<std::endl;
    	    			std::pair<Element*, team4::MetamodelElement*> element = findElement(i);
    	    			if (element.first != NULL) {
    	    			this->elements1.erase(i);
    	    			element.first->getGraphics()->getSceneNode()->detachObject(elem.first->getGraphics()->getManualObject());
    	    			Main::sMSceneMgr->destroyManualObject(element.first->getGraphics()->getManualObject());
    	    			Main::sMSceneMgr->destroySceneNode(element.first->getGraphics()->getSceneNode());
    	    			}
    	    		}
    }
    this->elements1.erase(A_Name);
    elem.first->getGraphics()->getSceneNode()->detachObject(elem.first->getGraphics()->getManualObject());
    Main::sMSceneMgr->destroyManualObject(elem.first->getGraphics()->getManualObject());
    Main::sMSceneMgr->destroySceneNode(elem.first->getGraphics()->getSceneNode());
}

void ElementCollection::removeAllElements()
{
    for(std::map<std::string, std::pair<Element* ,int>>::iterator i = elements1.begin(); i != elements1.end(); i++)
    {
        try
        {
            if (i->second.first != NULL)
            {
                delete i->second.first;
                i->second.first = NULL;
            }
            _controlerMetamodel->removeAll();
        }
        catch(...)
        {
            std::cout << "	catch() " << std::endl;
        }
    }
    this->elements1.clear();
    delete space;
    space = 0;
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::searchCloseElement(Ogre::Vector2* point)
{
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elements = getAllElements();
    for (std::vector<std::pair<Element*, team4::MetamodelElement*>>::const_iterator it = elements.begin(); it!= elements.end(); it++ )
    {
        if(isNode(it->second->getType()))
        {
            if (it->second->getType().compare(team4::JoinNode::ELEMENT_TYPE) == 0 || it->second->getType().compare(team4::ForkNode::ELEMENT_TYPE) == 0)
            {
                int size = it->first->getGraphics()->drawingAlgorihtm->getSize();
                if(it->first->getCenter()->x + size >= point->x && it->first->getCenter()->x - size <= point->x && it->first->getCenter()->y + size*20 >= point->y && it->first->getCenter()->y - size * 20 <= point->y)
                {
                    return *it;
                }

            }
            else if (it->second->getType().compare(team4::ActivityNode::ELEMENT_TYPE) == 0)
            {
                int sizeX = 20;
                int sizeY = 5;
                if(it->first->getCenter()->x + sizeX >= point->x && it->first->getCenter()->x - sizeX <= point->x && it->first->getCenter()->y + sizeY >= point->y && it->first->getCenter()->y - sizeY <= point->y)
                {
                    return *it;
                }
            }
            else if(it->second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) != 0 &&  it->second->getType().compare(team4::LoopNode::ELEMENT_TYPE) != 0 && it->second->getType().compare(team4::StructuredActivityNode::ELEMENT_TYPE) != 0 &&
            		it->first->getCenter()->x + 10.0 >= point->x && it->first->getCenter()->x - 10.0 <= point->x && it->first->getCenter()->y + 10.0 >= point->y && it->first->getCenter()->y - 10.0 <= point->y)
            {
            	return *it;
            }
            if (it->second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) == 0 ||  it->second->getType().compare(team4::LoopNode::ELEMENT_TYPE) == 0 || it->second->getType().compare(team4::StructuredActivityNode::ELEMENT_TYPE) == 0)
            {

                int width = it->first->getGraphics()->drawingAlgorihtm->widthE;
                int height = it->first->getGraphics()->drawingAlgorihtm->heightE;

                cout << "sizeW  " << width << "  sizeH " << height << std::endl;
                if(it->first->getCenter()->x + width >= point->x && it->first->getCenter()->x - width <= point->x && it->first->getCenter()->y + height >= point->y && it->first->getCenter()->y - height <= point->y)
                {
                    return *it;
                }
            }

        }
    }
    return std::pair<Element*, team4::MetamodelElement*>(NULL, NULL);
}

int ElementCollection::getDefaultWidthOfFragment(Ogre::Vector2* point){
	 std::pair<Element*, team4::MetamodelElement*> element = searchCloseFragment(point);
		  if(element.second != NULL) {
			  FragmentGraphics* elemGraphicsCasted = static_cast<FragmentGraphics*>(element.first->getGraphics());
			  if (elemGraphicsCasted->getWidth() >= 40)
				  return  elemGraphicsCasted->getWidth() - 20;
			  else
				  return  elemGraphicsCasted->getWidth();
		  }
	return 175;
}

int ElementCollection::getDefaultHeightOfFragment(Ogre::Vector2* point){
	std::pair<Element*, team4::MetamodelElement*> element = searchCloseFragment(point);
			  if(element.second != NULL) {
				  FragmentGraphics* elemGraphicsCasted = static_cast<FragmentGraphics*>(element.first->getGraphics());
				  if (elemGraphicsCasted->getHeight() >= 40)
					  return  elemGraphicsCasted->getHeight() - 20;
				  else
					  return  elemGraphicsCasted->getHeight();
			  }
		return 125;
}

Ogre::Vector2* ElementCollection::getDefaultCenterOfFragment(Ogre::Vector2* point){
	std::pair<Element*, team4::MetamodelElement*> element = searchCloseFragment(point);
	if(element.second != NULL && element.second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) == 0) {
		Ogre::Vector2* basepoint= element.first->getCenter();
		FragmentGraphics* elemGraphicsCasted = static_cast<FragmentGraphics*>(element.first->getGraphics());
		int height = elemGraphicsCasted->getHeight();
		int point_y = basepoint->y - point->y;
		int count = point_y/height;
		double y = basepoint->y + height / 2 - 40*count+20;
		std::cout<<"first y "<<point->y<<" count "<<count<<" y "<<y;
		return new Ogre::Vector2(basepoint->x, y);
	}
	else if (element.second != NULL){
		return element.first->getCenter();
	}
	return point;
}

std::pair<Element*, team4::MetamodelElement*> ElementCollection::searchCloseFragment(Ogre::Vector2* point)
{
	std::pair<Element*, team4::MetamodelElement*> to_return = std::pair<Element*, team4::MetamodelElement*>(NULL, NULL);
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elements = getAllElements();
    for (std::vector<std::pair<Element*, team4::MetamodelElement*>>::const_iterator it = elements.begin(); it!= elements.end(); it++ )
    {
        if(isNode(it->second->getType()))
        {
            if (it->second->getType().compare(team4::ConditionNode::ELEMENT_TYPE) == 0 ||  it->second->getType().compare(team4::LoopNode::ELEMENT_TYPE) == 0 || it->second->getType().compare(team4::StructuredActivityNode::ELEMENT_TYPE) == 0)
            {

                int width = it->first->getGraphics()->drawingAlgorihtm->widthE;
                int height = it->first->getGraphics()->drawingAlgorihtm->heightE;

                cout << "sizeW  " << width << "  sizeH " << height << std::endl;
                if(it->first->getCenter()->x + width >= point->x && it->first->getCenter()->x - width <= point->x && it->first->getCenter()->y + height >= point->y && it->first->getCenter()->y - height <= point->y)
                {
                	to_return =  *it;
                }
            }

        }
    }
     return  to_return;
}


bool ElementCollection::isNode(std::string type)
{

    //if(type == "ACTIVITY" || type == "MERGE" || type == "DECISION" || type == "FORK" || type == "JOIN" || type == "Fragment" || type == "FinalNode")
    //if(type == "ACTIVITY" || type == "MERGE" || type == "DECISION" || type == "Fork" || type == "JOIN" || type == "FinalNode" || type == "InitialNode")
    if (type == team4::ActivityNode::ELEMENT_TYPE ||
            type == team4::MergeNode::ELEMENT_TYPE ||
            type == team4::DecisionNode::ELEMENT_TYPE ||
            type == team4::ForkNode::ELEMENT_TYPE ||
            type == team4::JoinNode::ELEMENT_TYPE ||
            type == team4::FinalNode::ELEMENT_TYPE ||
            type == team4::InitialNode::ELEMENT_TYPE ||
            type == team4::ConditionNode::ELEMENT_TYPE ||
            type == team4::LoopNode::ELEMENT_TYPE ||
            type == team4::StructuredActivityNode::ELEMENT_TYPE)

    {
        return true;
    }

    return false;
}
bool fnccmp(Layer* one, Layer* two)
{
    return std::atoi(one->getName().substr(6,3).c_str()) < std::atoi(two->getName().substr(6,3).c_str());
}

std::vector<Layer*> ElementCollection::getLayers()
{
    std::vector<Layer*> vector;

    //std::vector<std::pair<Element*, team4::MetamodelElement*>>

    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == Layer::ELEMENT_TYPE)
        {
            vector.push_back(static_cast<Layer*>(iterator->second.first));
        }
        /*if (iterator->second.first; ->first.substr(0,6).compare("layer_") == 0)
    {
            vector.push_back(static_cast<Layer*>(iterator->second));
    }*/
    }
    std::sort(vector.begin(),vector.end(),fnccmp);
    return vector;
}


Layer* ElementCollection::getSelectedLayer()
{
    Layer* layer = NULL;
    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == Layer::ELEMENT_TYPE)
        {
            if (iterator->second.first->getLayerSelect())
                layer= (static_cast<Layer*>(iterator->second.first));
        }
    }
    return layer;
}
void ElementCollection::IncrementLayer()
{
    std::vector<Layer*> layers = ElementCollection::getLayers();
    unsigned int i = 0;
    for(; i < layers.size(); i++)
    {
        if (layers[i]->getLayerSelect())
        {
            if (i<layers.size()-1)
            {
                i++;
            }
            else
            {
                i = 0;
            }
            ElementCollection::selectLayer(layers[i]);
            break;
        }
    }
}

void ElementCollection::DecrementLayer()
{
    std::vector<Layer*> layers = ElementCollection::getLayers();
    unsigned int i = 0;
    for(i = layers.size()-1; i >= 0 ; i--)
    {
        if (layers[i]->getLayerSelect())
        {
            if (i>0)
            {
                i--;
            }
            else
            {
                i = layers.size()-1;
            }
            ElementCollection::selectLayer(layers[i]);
            break;
        }
    }
}
void ElementCollection::selectLayer(Layer* lay)
{
    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == Layer::ELEMENT_TYPE)
        {
            if (iterator->second.first == lay)
                iterator->second.first->setLayerSelect(true);
            else
                iterator->second.first->setLayerSelect(false);
        }
    }
}

void ElementCollection::setSelectedLayers()
{

    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == Layer::ELEMENT_TYPE)
        {
            if (iterator->second.first->getLayerSelect())
            {
                iterator->second.first->select();
            }
            else
            {
                iterator->second.first->unselected();
            }
        }
    }
}

void ElementCollection::setNormalLayers()
{
    typedef std::map<std::string, std::pair<Element* ,int>>::iterator it_type;
    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == Layer::ELEMENT_TYPE)
            iterator->second.first->unselected();
    }
}
std::vector<std::pair<Element*, team4::MetamodelElement*>> ElementCollection::getConnectors()
{
    std::vector<std::pair<Element*, team4::MetamodelElement*>> result;

    typedef std::map<std::string, std::pair<Element* ,int>>::iterator it_type;
    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if (metamodel->getType() == team4::FlowFinalNode::ELEMENT_TYPE)
        {
            result.push_back(std::pair<Element*, team4::MetamodelElement*>(iterator->second.first, metamodel));
        }
    }

    return result;
}

std::vector<LayerBookmark*> ElementCollection::getLayerBookmarks()
{
    std::vector<LayerBookmark*> vector;
    typedef std::map<std::string, std::pair<Element* ,int>>::iterator it_type;
    for(it_type iterator = elements1.begin(); iterator != elements1.end(); iterator++)
    {
        team4::MetamodelElement *metamodel = _controlerMetamodel->get(iterator->second.second);
        if ( metamodel->getType()  == LayerBookmark::ELEMENT_TYPE)
        {
            vector.push_back(static_cast<LayerBookmark*>(iterator->second.first));
        }
    }
    return vector;
}

// TODO: for now it works only with LayerBookmarkð...
LayerBookmark* ElementCollection::findBookmark(std::string name)
{
    std::vector<LayerBookmark*> vector = ElementCollection::getLayerBookmarks();
    for(std::vector<LayerBookmark*>::iterator i = vector.begin(); i != vector.end(); i++)
    {
        if ((*i)->getTarget()->getName().compare(name) == 0)
        {
            return (*i);
        }
    }
    return 0; // TODO: throw exception?
}

std::vector<std::pair<Element*, team4::MetamodelElement*>> ElementCollection::getAllElements()
{
    std::vector<std::pair<Element*, team4::MetamodelElement*>> result;

    /* for(std::map<std::string, Element*>::iterator i = elements.begin(); i != elements.end(); i++)
     {
         result.push_back((i->second));
     }*/
    for(std::map<std::string, std::pair<Element* ,int>>::iterator i = elements1.begin(); i != elements1.end(); i++)
    {
        result.push_back(std::pair<Element*, team4::MetamodelElement*>(i->second.first, _controlerMetamodel->get(i->second.second)));
    }
    return result;
}

Metamodel::Space* ElementCollection::getSpace()
{
    if (space == 0)
    {
        space = new Metamodel::Space();
    }
    return this->space;
}

void ElementCollection::setModel(std::map<std::string, std::pair<Element* ,int>> &A_elements)
{
    removeAllElements();
    elements1 = A_elements ;
}
