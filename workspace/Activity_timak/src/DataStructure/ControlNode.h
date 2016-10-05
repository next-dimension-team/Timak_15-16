/*
 * ControlNode.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef CONTROLNODE_H_
#define CONTROLNODE_H_

#include "ActivityNode.h"

namespace Metamodel {

class ControlNode: public ActivityNode {
public:
	ControlNode();
	virtual ~ControlNode();
};

} /* namespace Metamodel */

#endif /* CONTROLNODE_H_ */
