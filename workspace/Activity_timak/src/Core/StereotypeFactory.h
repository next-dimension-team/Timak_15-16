/*
 * StereotypeFactory.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef STEREOTYPEFACTORY_H_
#define STEREOTYPEFACTORY_H_

#include <OgreVector3.h>
#include <string>

#include "ElementFactory.h"

class Aggregation;
class Association;
class Element;
class Generalisation;
namespace Metamodel {
class Association;
} /* namespace Metamodel */


class StereotypeFactory: public ElementFactory
{
	public:
		StereotypeFactory(DrawManager* drawManager);
		virtual ~StereotypeFactory();

		Element* factoryMethod(Association* ass, std::string stereotypeName);
		Element*factoryMethod(int a);
		Element* factoryMethod(Aggregation* agg, std::string stereotypeName);
		Element* factoryMethod(Generalisation* gen, std::string stereotypeName);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

		Element* factoryMethod();

	private:
		Metamodel::Element* connector;
		std::string stereotypeName;
		Ogre::Vector3 differenceVector;

		Element* generalFactoryMethod(Metamodel::Association* connector, std::string stereotypeName);
};


#endif /* STEREOTYPEFACTORY_H_ */
