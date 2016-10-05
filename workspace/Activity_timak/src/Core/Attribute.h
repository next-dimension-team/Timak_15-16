/*
 * Attribute.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Element.h"

class Attribute: public Element
{
	friend class AttributeFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Attribute();

	protected:
		Attribute();
};

#endif /* ATTRIBUTE_H_ */
