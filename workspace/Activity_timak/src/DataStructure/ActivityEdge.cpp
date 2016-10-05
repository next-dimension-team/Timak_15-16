/*
 * ActivityEdge.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "ActivityEdge.h"

namespace Metamodel {

ActivityEdge::ActivityEdge() {
	source = 0;
	target = 0;
}

ActivityEdge::~ActivityEdge() {
	// TODO Auto-generated destructor stub
}

ActivityNode* ActivityEdge::getSource() {
	return source;
}

void ActivityEdge::setSource(ActivityNode* source) {
	this->source = source;
}

ActivityNode* ActivityEdge::getTarget() {
	return target;
}

void ActivityEdge::setTarget(ActivityNode* target) {
	this->target = target;
}

} /* namespace Metamodel */
