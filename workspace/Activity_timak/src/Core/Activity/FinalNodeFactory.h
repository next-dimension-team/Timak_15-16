/*
 * FinalNodeFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef FINALNODEFACTORY_H_
#define FINALNODEFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;
namespace Ogre {
class Vector2;
} /* namespace Ogre */


class FinalNodeFactory: public ElementFactory
{
	public:
		FinalNodeFactory(DrawManager* drawManager);
		virtual ~FinalNodeFactory();

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


#endif /* FINALNODEFACTORY_H_ */
