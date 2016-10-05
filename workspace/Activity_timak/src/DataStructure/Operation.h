/*
 * Operation.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include "BehavioralFeature.h"

namespace Metamodel {
class Class;
} /* namespace Metamodel */


namespace Metamodel {

class Operation: public BehavioralFeature {
public:
	Operation();
	virtual ~Operation();

	Metamodel::Class* getClass();
	void setClass(Metamodel::Class* c);

private:
	Metamodel::Class* c;
};

} /* namespace Metamodel */

#endif /* OPERATION_H_ */
