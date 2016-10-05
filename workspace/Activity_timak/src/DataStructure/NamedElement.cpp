/*
 * NamedElement.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "NamedElement.h"

namespace Metamodel {

NamedElement::NamedElement() {
	name.clear();
}

NamedElement::~NamedElement() {

}

std::string NamedElement::getName() {
	return name;
}

void NamedElement::setName(std::string s) {
	this->name = s;
}

} /* namespace Metamodel */
