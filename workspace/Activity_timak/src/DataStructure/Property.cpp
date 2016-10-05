/*
 * Property.cpp
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#include "Property.h"


namespace Metamodel {

Property::Property() {
	c = 0;
	//aggregation = AggregationKind::NONE;
}

Property::~Property() {
	// TODO Auto-generated destructor stub
}

AggregationKind Property::getAggregationKind() {
	return aggregation;
}

void Property::setAggregationKind(AggregationKind aggregation) {
	this->aggregation = aggregation;
}

Metamodel::Class* Property::getClass() {
	return c;
}

void Property::setClass(Metamodel::Class* c) {
	this->c = c;
}

} /* namespace Metamodel */
