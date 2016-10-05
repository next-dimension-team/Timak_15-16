#include "Serializer.h"
#include "../ApplicationManagement/ElementCollection.h"

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

#include "../HelperTeam4.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

namespace team4
{

Serializer::Serializer(const std::string& A_file) : _fileName(A_file)
{
    if (!Helpers::fileExist(_fileName))
    {
        _fileName = Helpers::getActualTime("format") + ".txt";
        DEF_ERROR("Unable to open file '" + A_file + "' , use default file " + _fileName);
    }
}

Serializer::Serializer()
{
    DEF_BEGIN;
    std::string folder = "save";
    Helpers::createDirectory(folder);
    _fileName = "./save/" + Helpers::getActualTime("format") + ".txt";
}
bool Serializer::run()
{
    DEF_BEGIN;
    ofstream myfile(_fileName, ios_base::out | std::ios::ate);
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elem = ElementCollection::getInstance()->getAllElements();

    if (myfile.is_open())
    {
        myfile << elem.size() << "\n";
    }
    else
    {
        DEF_ERROR("Unable to open file " + _fileName);
        return false;
    }

    for (auto i: elem)
    {
        if (myfile.is_open())
        {
            if (!callSerializationType(i, myfile))
            {
                DEF_ERROR("Model not saved correctly");
                return false;
            }
        }
        else
        {
            DEF_ERROR("Unable to open file " + _fileName);
            return false;
        }
    }
    myfile.close();
    DEF_DEBUG("Model saved correctly");
    return true;
}
bool Serializer::callSerializationType(const std::pair<Element*, team4::MetamodelElement*>& A_element, std::ofstream &A_stream)
{
    if (A_element.second->getType() == team4::ActivityNode::ELEMENT_TYPE)
    {
        return static_cast<team4::ActivityNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    if (A_element.second->getType() == team4::Alt::ELEMENT_TYPE)
    {
        return static_cast<team4::Alt*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::DecisionNode::ELEMENT_TYPE)
    {
        return static_cast<team4::DecisionNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::InitialNode::ELEMENT_TYPE)
    {
        return static_cast<team4::InitialNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::ActivityFinalNode::ELEMENT_TYPE)
    {
        return static_cast<team4::ActivityFinalNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::Action::ELEMENT_TYPE)
    {
        return static_cast<team4::Action*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::StructuredActivityNode::ELEMENT_TYPE)
    {
        return static_cast<team4::StructuredActivityNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4:: MergeNode::ELEMENT_TYPE)
    {
        return static_cast<team4::MergeNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::ForkNode::ELEMENT_TYPE)
    {
        return static_cast<team4::ForkNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::JoinNode::ELEMENT_TYPE)
    {
        return static_cast<team4::JoinNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::FlowFinalNode::ELEMENT_TYPE)
    {
        return static_cast<team4::FlowFinalNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::FinalNode::ELEMENT_TYPE)
    {
        return static_cast<team4::FinalNode*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == team4::ActivityEdge::ELEMENT_TYPE)
    {
        return static_cast<team4::ActivityEdge*>(A_element.second)->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    else if (A_element.second->getType() == Layer::ELEMENT_TYPE)
    {
        return static_cast<team4::FinalNode*>(A_element.second)->serialization(A_stream) && static_cast<Container*>(A_element.first)->serialization(A_stream);
    }
    else
    {
        return A_element.second->serialization(A_stream) && A_element.first->serialization(A_stream);
    }
    return false;
}

}



