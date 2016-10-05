/*
 * ActivityFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef ACTIVITYFACTORY_H_
#define ACTIVITYFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;
namespace Ogre {
class Vector2;
} /* namespace Ogre */


class ActivityFactory: public ElementFactory
{
	public:
		ActivityFactory(DrawManager* drawManager);
		virtual ~ActivityFactory();

		Element* factoryMethod(Container* c, std::string activityName, Ogre::Vector2* centerPoint);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Container* container;
		std::string activityName;
		Ogre::Vector2* centerPoint;
};


#endif /* ACTIVITYFACTORY_H_ */
