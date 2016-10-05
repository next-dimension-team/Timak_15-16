/*
 * InitialNodeAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef INITIALNODEALGORITHM_H_
#define INITIALNODEALGORITHM_H_

#include "../DrawingAlgorithm.h"

class InitialNode;
class NodeGraphics;

class InitialNodeAlgorithm: public DrawingAlgorithm {
public:
	InitialNodeAlgorithm();
	virtual ~InitialNodeAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	InitialNode* elem;
	NodeGraphics* elemGraphics;

	static const double SIZE;
};

#endif /* INITIALNODEALGORITHM_H_ */
