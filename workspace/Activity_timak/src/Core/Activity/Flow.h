/*
 * Flow.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef FLOW_H_
#define FLOW_H_

#include "../Element.h"

class Layer;

class Flow: public Element
{
	friend class FlowFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Flow();

		bool isOnLayer(Layer* layer);

	protected:
		Flow();
};


#endif /* FLOW_H_ */
