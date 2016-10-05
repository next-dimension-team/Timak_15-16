/*
 * AttributeFactory.h
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#ifndef ATTRIBUTEFACTORY_H_
#define ATTRIBUTEFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Class;


class AttributeFactory: public ElementFactory
{
	public:
		AttributeFactory(DrawManager* drawManager);
		virtual ~AttributeFactory();

		Element* factoryMethod(Class* cla, std::string attributeName);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);
};

#endif /* ATTRIBUTEFACTORY_H_ */
