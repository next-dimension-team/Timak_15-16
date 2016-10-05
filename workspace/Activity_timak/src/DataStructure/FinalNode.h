/*
 * FinalNode.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef FINALNODE_METAMODEL_H_
#define FINALNODE_METAMODEL_H_

#include "ControlNode.h"

namespace Metamodel {

class FinalNode: public ControlNode {
public:
	FinalNode();
	virtual ~FinalNode();
};

} /* namespace Metamodel */

#endif /* FINALNODE_H_ */
