/*
 * ActivityAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef ACTIVITYALGORITHM_H_
#define ACTIVITYALGORITHM_H_

#include "../DrawingAlgorithm.h"

class Activity;
class ActivityGraphics;
namespace Metamodel {
class Action;
} /* namespace Metamodel */
namespace Ogre {
class FontPtr;
} /* namespace Ogre */


class ActivityAlgorithm: public DrawingAlgorithm {
public:
	ActivityAlgorithm();
	virtual ~ActivityAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
	double getFullWidth(Element* elem);
	double getFullHeight(Element* elem);

	static void cleanUp();

private:
	Activity* elem;
	Metamodel::Action* elemData;
	ActivityGraphics* elemGraphics;

	double minWidth;
	double lineHeight;
	double charWidthMultiplier;
	double borderHorizontalWidth;
	double borderVerticalWidth;
	double cornerSize;

	double getWidth();
	double getHeight();

	static Ogre::FontPtr FONT;

	void initFont();
};

#endif /* ACTIVITYALGORITHM_H_ */
