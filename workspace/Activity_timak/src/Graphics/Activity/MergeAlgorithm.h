#ifndef MERGEALGORITHM_H_
#define MERGEALGORITHM_H_

#include "../DrawingAlgorithm.h"

class Merge;
class MergeGraphics;

class MergeAlgorithm: public DrawingAlgorithm {
public:
	MergeAlgorithm();
	virtual ~MergeAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullSize();

private:
	Merge* elem;
	MergeGraphics* elemGraphics;

	static const double SIZE;
};

#endif
