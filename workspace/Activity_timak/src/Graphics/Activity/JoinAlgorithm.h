#ifndef JOINALGORITHM_H_
#define JOINALGORITHM_H_

#include "../DrawingAlgorithm.h"

class Join;
class JoinGraphics;

class JoinAlgorithm: public DrawingAlgorithm {
public:
	JoinAlgorithm();
	virtual ~JoinAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	Join* elem;
	JoinGraphics* elemGraphics;

	static const double SIZE;
};

#endif
