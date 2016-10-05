/*
 * GeneralisationAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef GENERALISATIONALGORITHM_H_
#define GENERALISATIONALGORITHM_H_

#include "DrawingAlgorithm.h"

class GeneralisationAlgorithm: public DrawingAlgorithm {
public:
	GeneralisationAlgorithm();
	virtual ~GeneralisationAlgorithm();
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	virtual void draw(const std::string& A_name);
};

#endif /* GENERALISATIONALGORITHM_H_ */
