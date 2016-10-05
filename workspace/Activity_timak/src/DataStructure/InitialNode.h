/*
 * InitialNode.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef INITIALNODE_METAMODEL_H_
#define INITIALNODE_METAMODEL_H_

#include "ControlNode.h"


namespace Metamodel {

class InitialNode: public ControlNode {
public:
	InitialNode();
	virtual ~InitialNode();
};

} /* namespace Metamodel */

#endif /* INITIALNODE_H_ */
