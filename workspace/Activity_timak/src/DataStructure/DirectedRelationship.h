/*
 * DirectedRelationship.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef DIRECTEDRELATIONSHIP_H_
#define DIRECTEDRELATIONSHIP_H_

#include "Relationship.h"

namespace Metamodel {

class DirectedRelationship: public Relationship {
public:
	DirectedRelationship();
	virtual ~DirectedRelationship();
};

} /* namespace Metamodel */

#endif /* DIRECTEDRELATIONSHIP_H_ */
