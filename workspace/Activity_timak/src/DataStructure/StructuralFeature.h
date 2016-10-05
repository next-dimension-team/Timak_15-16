/*
 * StructuralFeature.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef STRUCTURALFEATURE_H_
#define STRUCTURALFEATURE_H_

#include "Feature.h"

namespace Metamodel {

class StructuralFeature: public Feature {
public:
	StructuralFeature();
	virtual ~StructuralFeature();
};

} /* namespace Metamodel */

#endif /* STRUCTURALFEATURE_H_ */
