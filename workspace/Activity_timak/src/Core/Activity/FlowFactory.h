/*
 * FlowFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef FLOWFACTORY_H_
#define FLOWFACTORY_H_

#include <string>

#include "../ElementFactory.h"

namespace Metamodel {
class ActivityNode;
} /* namespace Metamodel */

namespace team4
{
	class MetamodelElement;
	class ActivityNode;
}


class FlowFactory: public ElementFactory
{
	public:
		FlowFactory(DrawManager* drawManager);
		virtual ~FlowFactory();

		Element* factoryMethod(team4::ActivityNode* A_source, team4::ActivityNode* A_target);

		Element* factoryMethod(std::pair<Element*, team4::MetamodelElement*>& A_source, std::pair<Element*, team4::MetamodelElement*>& A_target);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		team4::ActivityNode* source;
		team4::ActivityNode* target;
};


#endif /* FLOWFACTORY_H_ */
