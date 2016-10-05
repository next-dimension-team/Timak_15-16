/*
 * AssociationFactory.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ASSOCIATIONFACTORY_H_
#define ASSOCIATIONFACTORY_H_

#include <string>

#include "ElementFactory.h"

class AssociationEndingData;
class Class;
namespace Metamodel {
class Property;
} /* namespace Metamodel */


class AssociationFactory: public ElementFactory
{
	public:
		AssociationFactory(DrawManager* drawManager);
		virtual ~AssociationFactory();

		Element* factoryMethod(Class* source, Class* target);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Metamodel::Property* source;
		Metamodel::Property* target;
};

#endif /* ASSOCIATIONFACTORY_H_ */
