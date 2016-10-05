/*
 * Aggregation.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */


#include "Aggregation.h"

#include "../ApplicationManagement/ElementCollection.h"
#include "Class.h"
#include "Utilities.h"


const std::string Aggregation::ELEMENT_TYPE = "AGGREGATION";

Aggregation::Aggregation() : Element()
{

}

Aggregation::~Aggregation()
{

}

bool Aggregation::isOnLayer(Layer* layer)
{
	if (layer == 0) return false;

	Class* source = static_cast<Class*>(Utilities::getConnectorSource(this->data));
	Class* target = static_cast<Class*>(Utilities::getConnectorTarget(this->data));

	if (ElementCollection::getInstance()->findLayerOfClass(source) == layer &&
		ElementCollection::getInstance()->findLayerOfClass(target) == layer) {
		return true;
	} else {
		return false;
	}
}

