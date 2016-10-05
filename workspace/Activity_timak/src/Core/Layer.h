/*
 * Layer.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef LAYER_CORE_H_
#define LAYER_CORE_H_

#include <string>
#include <vector>

#include "Class.h"
#include "Container.h"

class Layer: public Container
{
	friend class LayerFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Layer();

		Class* findClass(std::string className);
		void addClass(Class* c);
		std::vector<Class*> getClasses();


	protected:
		Layer();
};

#endif /* LAYER_H_ */
