/*
 * StereotypeAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef STEREOTYPEALGORITHM_H_
#define STEREOTYPEALGORITHM_H_

#include "DrawingAlgorithm.h"

class Stereotype;
class StereotypeGraphics;
namespace Metamodel {
class Association;
} /* namespace Metamodel */
namespace Ogre {
class FontPtr;
} /* namespace Ogre */


class StereotypeAlgorithm: public DrawingAlgorithm {
public:
	StereotypeAlgorithm();
	virtual ~StereotypeAlgorithm();

	virtual void draw(const std::string& A_name);

	static void cleanUp();

private:
	Stereotype* elem;
	Metamodel::Association* elemData;
	StereotypeGraphics* elemGraphics;

	double minWidth;
	double lineHeight;
	double charWidthMultiplier;
	double borderHorizontalWidth;
	double borderVerticalWidth;
	double borderTriangleWidth;

	double getWidth();
	double getHeight();

	static Ogre::FontPtr FONT;

	void initFont();
};

#endif /* STEREOTYPEALGORITHM_H_ */
