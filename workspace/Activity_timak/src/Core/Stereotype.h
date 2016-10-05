/*
 * Stereotype.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef STEREOTYPE_H_
#define STEREOTYPE_H_

#include "Element.h"

class Stereotype: public Element
{
	friend class StereotypeFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Stereotype();

	protected:
		Stereotype();
};

#endif /* STEREOTYPE_H_ */
