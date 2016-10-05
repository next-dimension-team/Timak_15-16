/*
 * Association.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "Association.h"

namespace Metamodel {

Association::Association() {
	stereotype.clear();
}

Association::~Association() {

}

void Association::addMemberEnd(Metamodel::Property* p) {
	memberEnd.push_back(p);
}

std::vector<Property*> Association::getMemberEnds() {
	return std::vector<Property*>(memberEnd);
}

std::string Association::getStereotype() {
	return stereotype;
}

void Association::setStereotype(std::string s) {
	this->stereotype = s;
}

} /* namespace Metamodel */
