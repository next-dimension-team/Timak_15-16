/*
 * Decision.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef DECISION_H_
#define DECISION_H_

class Layer;

#include "../Element.h"

class Decision: public Element
{
	friend class DecisionFactory;

	public:
		static const std::string ELEMENT_TYPE;
		virtual ~Decision();

	protected:
		Decision();
};


#endif /* DECISION_H_ */
