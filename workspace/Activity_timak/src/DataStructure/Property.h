/*
 * Property.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "AggregationKind.h"
#include "StructuralFeature.h"

namespace Metamodel {
class Class;
} /* namespace Metamodel */


namespace Metamodel {

class Property: public StructuralFeature {
public:
	Property();
	virtual ~Property();

	AggregationKind getAggregationKind();
	void setAggregationKind(AggregationKind aggregation);

	Metamodel::Class* getClass();
	void setClass(Metamodel::Class* c);

private:
	AggregationKind aggregation;
	Metamodel::Class* c;
};

} /* namespace Metamodel */

#endif /* PROPERTY_H_ */
