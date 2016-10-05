#ifndef FORKALGORITHM_H_
#define FORKALGORITHM_H_

#include "../DrawingAlgorithm.h"

class Fork;
class ForkGraphics;

class ForkAlgorithm: public DrawingAlgorithm {
public:
	ForkAlgorithm();
	virtual ~ForkAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	Fork* elem;
	ForkGraphics* elemGraphics;

	static const double SIZE;
};

#endif
