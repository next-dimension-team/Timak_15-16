/*
 * FlowAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef FLOWALGORITHM_H_
#define FLOWALGORITHM_H_

#include "../DrawingAlgorithm.h"

namespace Ogre {
class FontPtr;
} /* namespace Ogre */

class FlowAlgorithm: public DrawingAlgorithm {
public:
	FlowAlgorithm();
	virtual ~FlowAlgorithm();

	void initFont();
	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	static Ogre::FontPtr FONT;
	void cleanUp();
};

#endif /* FLOWALGORITHM_H_ */
