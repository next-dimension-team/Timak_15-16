/*
 * Class.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "Class.h"

#include <algorithm>
#include <iterator>

//#include <string>

namespace Metamodel {

Class::Class() {
	// TODO Auto-generated constructor stub

}

Class::~Class() {
	for(std::vector<Operation*>::iterator i = ownedOperation.begin(); i != ownedOperation.end(); i++) {
		delete *i;
	}
	ownedOperation.clear();

	for(std::vector<Property*>::iterator i = ownedAttribute.begin(); i != ownedAttribute.end(); i++) {
		delete *i;
	}
	ownedAttribute.clear();
}

void Class::addOperation(Operation* o) {
	ownedOperation.push_back(o);
}
void Class::removeOperation(Operation* o) {
	ownedOperation.erase(std::remove(ownedOperation.begin(), ownedOperation.end(), o), ownedOperation.end());
}
std::vector<Operation*> Class::getOperations() {
	return std::vector<Operation*>(ownedOperation);
}

void Class::addAttribute(Property* p) {
	ownedAttribute.push_back(p);
}
void Class::removeAttribute(Property* p) {
	ownedAttribute.erase(std::remove(ownedAttribute.begin(), ownedAttribute.end(), p), ownedAttribute.end());
}
std::vector<Property*> Class::getAttributes() {
	return std::vector<Property*>(ownedAttribute);
}

} /* namespace Metamodel */

