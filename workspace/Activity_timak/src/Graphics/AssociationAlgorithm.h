/*
 * AssociationAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef ASSOCIATIONALGORITHM_H_
#define ASSOCIATIONALGORITHM_H_

#include "DrawingAlgorithm.h"

class AssociationAlgorithm: public DrawingAlgorithm {
public:
	AssociationAlgorithm();
	virtual ~AssociationAlgorithm();
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	virtual void draw(const std::string& A_name);
};


#endif /* ASSOCIATIONALGORITHM_H_ */
