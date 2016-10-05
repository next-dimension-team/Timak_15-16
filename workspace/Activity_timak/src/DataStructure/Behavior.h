/*
 * Behavior.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "Class.h"

namespace Metamodel {
namespace BasicBehaviors {

class Behavior: public Class {
public:
	Behavior();
	virtual ~Behavior();
};

} /* namespace BasicBehaviors */

namespace CompleteActivities {

class Behavior: public BasicBehaviors::Behavior {
public:
	Behavior();
	virtual ~Behavior();
};

} /* namespace CompleteActivities */
} /* namespace Metamodel */
#endif /* BEHAVIOR_H_ */

