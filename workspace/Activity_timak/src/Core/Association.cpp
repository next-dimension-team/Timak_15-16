/*
 * Association.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#include "Association.h"

#include "../ApplicationManagement/ElementCollection.h"
#include "Class.h"
#include "Utilities.h"


const std::string Association::ELEMENT_TYPE = "ASSOCIATION";

Association::Association() : Element()
{

}

Association::~Association()
{

}

bool Association::isOnLayer(Layer* layer)
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

