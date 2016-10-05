/*
 *      Author: Bc. Andrej Železòák
 *      Email: azeleznak@gmail.com
 */

#include "ControlerMetamodel.h"

#include <vector>
#include <iostream>

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


#include "Metamodel.h"

namespace team4
{
ControlerMetamodel::ControlerMetamodel(MetaModel &A_metamodel) : _metamodel(&A_metamodel), _idCount(0)
{}

ControlerMetamodel::~ControlerMetamodel()
{}

MetamodelElement* ControlerMetamodel::add(const std::string &A_type)
{
    if (A_type == ActivityNode::ELEMENT_TYPE)
    {
    	ActivityNode* element = new ActivityNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == Alt::ELEMENT_TYPE)
    {
        Alt* element = new Alt();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == DecisionNode::ELEMENT_TYPE)
    {
        DecisionNode* element = new DecisionNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == InitialNode::ELEMENT_TYPE)
    {
        InitialNode* element = new InitialNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == ActivityFinalNode::ELEMENT_TYPE)
    {
        ActivityFinalNode* element = new ActivityFinalNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == Action::ELEMENT_TYPE)
    {
        Action* element = new Action();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == StructuredActivityNode::ELEMENT_TYPE)
    {
        StructuredActivityNode* element = new StructuredActivityNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == MergeNode::ELEMENT_TYPE)
    {
        MergeNode* element = new MergeNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == ForkNode::ELEMENT_TYPE)
    {
        ForkNode* element = new ForkNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == JoinNode::ELEMENT_TYPE)
    {
        JoinNode* element = new JoinNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == FlowFinalNode::ELEMENT_TYPE)
    {
        FlowFinalNode* element = new FlowFinalNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else if (A_type == FinalNode::ELEMENT_TYPE)
    {
        FinalNode* element = new FinalNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else
    {
		MetamodelElement * element = new MetamodelElement();
		element->setId(_idCount);
		element->setType(A_type);
		element->generateName();
		_metamodel->array.push_back(element);
		_idCount++;
		 return element;
    }
    return NULL;
}

MetamodelElement* ControlerMetamodel::add(const std::string &A_type, ActivityNode *A_source, ActivityNode *A_target, const std::string& A_text)
{
    DEF_BEGIN;
    // TODO dorobit rozny pocet hran;
    if (A_type == ActivityEdge::ELEMENT_TYPE)
    {
        ActivityEdge* element = new ActivityEdge();
        element->setId(_idCount);
        element->generateName();
        element->source = A_source;
        element->target = A_target;
        element->text = A_text;
        if (A_source != NULL && A_target != NULL)
        {
            A_source->outgoing.push_back(element);
            A_target->incoming.push_back(element);
        }
        else
        {
            delete element;
            return NULL;
        }
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else
    {
        return add(A_type);
    }
    return NULL;
}

MetamodelElement* ControlerMetamodel::add(const std::string &A_type, const std::string& A_condition)
{
    if (A_type == Clause::ELEMENT_TYPE)
    {
    	Clause* element = new Clause();
        element->setId(_idCount);
        element->generateName();
        element->condiotion = A_condition;
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else
    {
        return add(A_type);
    }
    return NULL;
}

MetamodelElement* ControlerMetamodel::add(const std::string &A_type, const std::string&  A_init, const std::string& A_cond)
{
    if (A_type == LoopNode::ELEMENT_TYPE)
    {
    	LoopNode* element = new LoopNode();
        element->setId(_idCount);
        element->generateName();
        element->init = A_init;
        element->cond = A_cond;
        _metamodel->array.push_back(element);
        _idCount++;
        return element;
    }
    else
    {
        return add(A_type);
    }
    return NULL;
}

MetamodelElement* ControlerMetamodel::add(const std::string &A_type, const vector<std::string>&  A_condition)
{
	// alt
    if (A_type == ConditionNode::ELEMENT_TYPE)
    {
    	ConditionNode* element = new ConditionNode();
        element->setId(_idCount);
        element->generateName();
        _metamodel->array.push_back(element);
        _idCount++;
        for (auto i: A_condition)
        {
        	element->cluase.push_back(static_cast<Clause*>(add(Clause::ELEMENT_TYPE, i)));
        }
        return element;
    }
    else
    {
        return add(A_type);
    }
    return NULL;
}


MetamodelElement* ControlerMetamodel::get(int A_id)
{
    if (A_id >= 0)
    {
        for (int i=0; i < (int)_metamodel->array.size(); i++)
        {
            if (_metamodel->array[i]->getId() == A_id)
            {
                return _metamodel->array[i];
            }
        }
    }
    return NULL;
}

bool ControlerMetamodel::remove(int A_id)
{
    for (int i=0; i < (int)_metamodel->array.size(); i++)
    {
        if (_metamodel->array[i]->getId() == A_id)
        {
            //
            /* if (_metamodel->array[i]->type == "ActivityEdge")
             {
                 ActivityEdge *activityEdge = dynamic_cast<ActivityEdge>(_metamodel->array[i]);

                 // TODO pridat vymazavanie hran

                 activityEdge->source

                 _metamodel->array[i]->source = ;
                 _metamodel->array[i]->target = ;
                 ActivityNode
             }*/

            //correct deallocation
            delete(_metamodel->array[i]);
            _metamodel->array.erase(_metamodel->array.begin() + i);
        }
    }
    return false;
}

bool ControlerMetamodel::update(int A_id)
{
    return false;
}

bool ControlerMetamodel::removeAll()
{
	for ( auto i: _metamodel->array)
	{
		delete i;
	}
	_metamodel->array.clear();
	return true;
}


} /* namespace team4 */
