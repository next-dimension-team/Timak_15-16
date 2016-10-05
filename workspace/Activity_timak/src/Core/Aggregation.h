/*
 * Aggregation.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef AGGREGATION_H_
#define AGGREGATION_H_

#include <string>

class Layer;

class AssociationData;
class AssociationGraphics;

#include "Element.h"

class Aggregation: public Element
{
	friend class AggregationFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Aggregation();

		bool isOnLayer(Layer* layer);

	protected:
		Aggregation();
};

#endif /* AGGREGATION_H_ */
