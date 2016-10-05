/*
 * Class.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef CLASS_CORE_H_
#define CLASS_CORE_H_

#include <string>

#include "Element.h"

namespace Metamodel {
class Class;
} /* namespace Metamodel */

class Class: public Element
{
	friend class ClassFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Class();

		std::string getAttributesText();
		std::string getMethodsText();

	protected:
		Class();
};

#endif /* CLASS_CORE_H_ */
