/*
 * Association.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef ASSOCIATION_CORE_H_
#define ASSOCIATION_CORE_H_

#include <string>

#include "Element.h"

class Layer;


class Association: public Element
{
	friend class AssociationFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Association();

		bool isOnLayer(Layer* layer);

	protected:
		Association();
};

#endif /* ASSOCIATION_CORE_H_ */
