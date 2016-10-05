/*
 * ControlFlow.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef CONTROLFLOW_H_
#define CONTROLFLOW_H_

#include "ActivityEdge.h"

namespace Metamodel {

class ControlFlow: public ActivityEdge {
public:
	ControlFlow();
	virtual ~ControlFlow();
};

} /* namespace Metamodel */

#endif /* CONTROLFLOW_H_ */
