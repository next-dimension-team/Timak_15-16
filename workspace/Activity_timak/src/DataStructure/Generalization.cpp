/*
 * Generalization.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "Generalization.h"

namespace Metamodel {

Generalization::Generalization() {
	general = 0;
	specific = 0;
}

Generalization::~Generalization() {
	// TODO Auto-generated destructor stub
}

Classifier* Generalization::getGeneral() {
	return general;
}
void Generalization::setGeneral(Classifier* general) {
	this->general = general;
}

Classifier* Generalization::getSpecific() {
	return specific;
}
void Generalization::setSpecific(Classifier* specific) {
	this->specific = specific;
}

} /* namespace Metamodel */
