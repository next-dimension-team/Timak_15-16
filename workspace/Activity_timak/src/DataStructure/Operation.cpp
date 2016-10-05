/*
 * Operation.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "Operation.h"


namespace Metamodel {

Operation::Operation() {
	c = 0;
}

Operation::~Operation() {
	// TODO Auto-generated destructor stub
}

Metamodel::Class* Operation::getClass() {
	return c;
}

void Operation::setClass(Metamodel::Class* c) {
	this->c = c;
}

} /* namespace Metamodel */
