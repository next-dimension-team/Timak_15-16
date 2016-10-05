/*
 * MethodFactory.h
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#ifndef METHODFACTORY_H_
#define METHODFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Class;


class MethodFactory: public ElementFactory
{
	public:
		MethodFactory(DrawManager* drawManager);
		virtual ~MethodFactory();

		Element* factoryMethod(Class* cla, std::string operationName);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);
};

#endif /* METHODFACTORY_H_ */
