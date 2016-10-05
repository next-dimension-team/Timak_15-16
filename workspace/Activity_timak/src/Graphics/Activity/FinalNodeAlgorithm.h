/*
 * FinalNodeAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef FINALNODEALGORITHM_H_
#define FINALNODEALGORITHM_H_

#include "../DrawingAlgorithm.h"

class FinalNode;
class NodeGraphics;

class FinalNodeAlgorithm: public DrawingAlgorithm {
public:
	FinalNodeAlgorithm();
	virtual ~FinalNodeAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	FinalNode* elem;
	NodeGraphics* elemGraphics;

	static const double SIZE;
};

#endif /* FINALNODEALGORITHM_H_ */
