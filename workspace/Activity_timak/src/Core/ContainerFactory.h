/*
 * ContainerFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef CONTAINERFACTORY_H_
#define CONTAINERFACTORY_H_

#include <string>

#include "ElementFactory.h"

namespace Ogre {
class Vector2;
} /* namespace Ogre */

class ContainerFactory: public ElementFactory
{
	public:
		ContainerFactory(DrawManager* drawManager);
		virtual ~ContainerFactory();

		Element* factoryMethod(Element* elemPar, Ogre::Vector2* centerPoint);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Element* elem;
		Ogre::Vector2* centerPoint;
};


#endif /* CONTAINERFACTORY_H_ */
