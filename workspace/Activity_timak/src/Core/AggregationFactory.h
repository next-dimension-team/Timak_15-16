/*
 * AggregationFactory.h
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#ifndef AGGREGATIONFACTORY_H_
#define AGGREGATIONFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Class;
namespace Metamodel {
class Property;
} /* namespace Metamodel */


class AssociationEndingData;

class AggregationFactory: public ElementFactory
{
	public:
		AggregationFactory(DrawManager* drawManager);
		virtual ~AggregationFactory();

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

#endif /* AGGREGATIONFACTORY_H_ */
