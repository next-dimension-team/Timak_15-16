/*
 * Generalisation.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef GENERALISATION_H_
#define GENERALISATION_H_

#include <string>

#include "Element.h"

class Layer;

class Generalisation: public Element
{
	friend class GeneralisationFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Generalisation();

		bool isOnLayer(Layer* layer);

	protected:
		Generalisation();
};

#endif /* GENERALISATION_H_ */
