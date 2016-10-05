/*
 * ActivityEdge.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef ACTIVITYEDGE_H_
#define ACTIVITYEDGE_H_

#include "RedefinableElement.h"

namespace Metamodel {
class ActivityNode;
} /* namespace Metamodel */

namespace Metamodel {

class ActivityEdge: public RedefinableElement {
public:
	ActivityEdge();
	virtual ~ActivityEdge();

	ActivityNode* getSource();
	void setSource(ActivityNode* source);
	ActivityNode* getTarget();
	void setTarget(ActivityNode* target);

private:
	ActivityNode* source;
	ActivityNode* target;
};

} /* namespace Metamodel */

#endif /* ACTIVITYEDGE_H_ */
