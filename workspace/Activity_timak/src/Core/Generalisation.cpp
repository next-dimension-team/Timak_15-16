/*
 * Generalisation.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "Generalisation.h"

#include "../ApplicationManagement/ElementCollection.h"
#include "Class.h"
#include "Utilities.h"


const std::string Generalisation::ELEMENT_TYPE = "GENERALISATION";

Generalisation::Generalisation() : Element()
{

}

Generalisation::~Generalisation()
{

}

bool Generalisation::isOnLayer(Layer* layer)
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

