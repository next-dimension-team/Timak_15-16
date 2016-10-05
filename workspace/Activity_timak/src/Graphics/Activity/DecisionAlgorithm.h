/*
 * DecisionAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef DECISIONALGORITHM_H_
#define DECISIONALGORITHM_H_

#include "../DrawingAlgorithm.h"

class Decision;
class DecisionGraphics;

class DecisionAlgorithm: public DrawingAlgorithm {
public:
	DecisionAlgorithm();
	virtual ~DecisionAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	Decision* elem;
	DecisionGraphics* elemGraphics;

	static const double SIZE;
};

#endif /* DECISIONALGORITHM_H_ */
