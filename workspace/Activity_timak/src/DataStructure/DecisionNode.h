/*
 * DecisionNode.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef DECISIONNODEA_H_
#define DECISIONNODEA_H_

#include "ControlNode.h"

namespace Metamodel
{

class DecisionNode: public ControlNode
{
	public:
		DecisionNode();
		virtual ~DecisionNode();
};

} /* namespace Metamodel */

#endif /* DECISIONNODE_H_ */
