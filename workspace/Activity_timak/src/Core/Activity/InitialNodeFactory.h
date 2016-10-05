/*
 * InitialNodeFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef INITIALNODEFACTORY_H_
#define INITIALNODEFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;
namespace Ogre {
class Vector2;
} /* namespace Ogre */


class InitialNodeFactory: public ElementFactory
{
	public:
		InitialNodeFactory(DrawManager* drawManager);
		virtual ~InitialNodeFactory();

		Element* factoryMethod(Container* c, Ogre::Vector2* centerPoint);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Container* container;
		Ogre::Vector2* centerPoint;
};


#endif /* INITIALNODEFACTORY_H_ */
