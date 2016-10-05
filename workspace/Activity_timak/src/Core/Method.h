/*
 * Method.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef METHOD_H_
#define METHOD_H_

#include "Element.h"

class Method: public Element
{
	friend class MethodFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Method();

	protected:
		Method();
};

#endif /* METHOD_H_ */
