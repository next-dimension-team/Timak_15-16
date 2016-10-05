/*
 * Activity.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include "Behavior.h"

namespace Metamodel {

class Activity: public CompleteActivities::Behavior {
public:
	Activity();
	virtual ~Activity();
};

} /* namespace Metamodel */

#endif /* ACTIVITY_H_ */
