/*
 * Relationship.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef RELATIONSHIP_H_
#define RELATIONSHIP_H_

#include "Element.h"

namespace Metamodel {

class Relationship: public virtual Metamodel::Element {
public:
	Relationship();
	virtual ~Relationship();
};

} /* namespace Metamodel */

#endif /* RELATIONSHIP_H_ */
