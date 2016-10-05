/*
 * ClassAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef CLASSALGORITHM_H_
#define CLASSALGORITHM_H_

#include "DrawingAlgorithm.h"

class Class;
class ClassGraphics;
namespace Metamodel {
class Class;
} /* namespace Metamodel */
namespace Ogre {
class FontPtr;
} /* namespace Ogre */


class ClassAlgorithm: public DrawingAlgorithm {
public:
	ClassAlgorithm();
	virtual ~ClassAlgorithm();

	virtual void draw(const std::string& A_name);

	double getFullWidth(Element* elem);
	double getFullHeight(Element* elem);

	static void cleanUp();

private:
	Class* elem;
	Metamodel::Class* elemData;
	ClassGraphics* elemGraphics;

	double minWidth;
	double lineHeight;
	double charWidthMultiplier;
	double borderHorizontalWidth;
	double borderVerticalWidth;

	double getWidth();
	double getHeight();
	double getAttributesHeight();
	double getMethodsHeight();
	double getHeaderHeight();

	static Ogre::FontPtr FONT_HEADER;
	static Ogre::FontPtr FONT_ATTRIBUTE;

	void initFonts();
};

#endif /* CLASSALGORITHM_H_ */
