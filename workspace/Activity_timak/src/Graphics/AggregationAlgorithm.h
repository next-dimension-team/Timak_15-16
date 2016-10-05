/*
 * AggregationAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef AGGREGATIONALGORITHM_H_
#define AGGREGATIONALGORITHM_H_

#include "DrawingAlgorithm.h"

class AggregationAlgorithm: public DrawingAlgorithm {
public:
	AggregationAlgorithm();
	virtual ~AggregationAlgorithm();
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	virtual void draw(const std::string& A_name);
};

#endif /* AGGREGATIONALGORITHM_H_ */
