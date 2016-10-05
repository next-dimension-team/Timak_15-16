/*
 * Flow.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "Flow.h"

#include <string>

#include "../../ApplicationManagement/ElementCollection.h"
#include "../../DataStructure/ControlFlow.h"
#include "../Utilities.h"


const std::string Flow::ELEMENT_TYPE = "FLOW";

Flow::Flow() : Element()
{}

Flow::~Flow()
{}

bool Flow::isOnLayer(Layer* layer)
{
    if (layer == 0)
        return false;

    Metamodel::ControlFlow* fd = 0;

    fd = dynamic_cast<Metamodel::ControlFlow*>(this->data);
    Element* source = Utilities::getConnectorSource(fd);
    Element* target = Utilities::getConnectorTarget(fd);

    if (ElementCollection::getInstance()->findLayerOfElement(source) == layer &&
            ElementCollection::getInstance()->findLayerOfElement(target) == layer)
    {
        return true;
    }
    else
    {
        return false;
    }
}
