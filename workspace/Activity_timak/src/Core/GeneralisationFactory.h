/*
 * GeneralisationFactory.h
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#ifndef GENERALISATIONFACTORY_H_
#define GENERALISATIONFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Class;
namespace Metamodel {
class Class;
} /* namespace Metamodel */


class GeneralisationFactory: public ElementFactory
{
	public:
		GeneralisationFactory(DrawManager* drawManager);
		virtual ~GeneralisationFactory();

		Element* factoryMethod(Class* source, Class* target);
		Element* factoryMethod(Metamodel::Class* source, Metamodel::Class* target);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Metamodel::Class* source;
		Metamodel::Class* target;
};

#endif /* GENERALISATIONFACTORY_H_ */
