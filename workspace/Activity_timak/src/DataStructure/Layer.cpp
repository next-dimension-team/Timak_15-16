/*
 * Layer.cpp
 *
 *  Created on: 27.4.2014
 *      Author: Schade
 */

#include "Layer.h"

#include <iterator>

namespace Metamodel {

Layer::Layer() {
	// TODO Auto-generated constructor stub

}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

void Layer::addElement(Metamodel::NamedElement* e)
{
	this->elements.push_back(e);
}

std::vector<Metamodel::NamedElement*> Layer::getElements()
{
	return this->elements;
}

bool Layer::containsElement(Metamodel::NamedElement* searched) {
	for(std::vector<Metamodel::NamedElement*>::iterator i = elements.begin(); i != elements.end(); i++) {
		if (searched == *i) {
			return true;
		}
	}
	return false;
}

} /* namespace Metamodel */
