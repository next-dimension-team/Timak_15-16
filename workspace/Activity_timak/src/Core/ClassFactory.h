/*
 * ClassFactory.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef CLASSFACTORY_H_
#define CLASSFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Layer;
namespace Ogre {
class Vector2;
} /* namespace Ogre */


class ClassFactory: public ElementFactory
{
	public:
		ClassFactory(DrawManager* drawManager);
		virtual ~ClassFactory();

		Element* factoryMethod(Layer* lay, std::string className, Ogre::Vector2* centerPoint);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Layer* lay;
		std::string className;
		Ogre::Vector2* centerPoint;
};

#endif /* CLASSFACTORY_H_ */
