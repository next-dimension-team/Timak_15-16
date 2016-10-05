/*
 * ForkNode.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef FORKNODE_H_
#define FORKNODE_H_

#include "ControlNode.h"

namespace Metamodel {

class ForkNode: public ControlNode {
public:
	ForkNode();
	virtual ~ForkNode();
};

} /* namespace Metamodel */

#endif /* FORKNODE_H_ */
