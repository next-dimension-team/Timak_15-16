/*
 * LayerFactory.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef LAYERFACTORY_H_
#define LAYERFACTORY_H_

#include <string>

#include "ElementFactory.h"

class LayerFactory: public ElementFactory
{
	public:
		LayerFactory(DrawManager* drawManager);
		virtual ~LayerFactory();

		Element* factoryMethod();

		void resetMaxLayerLevel();

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		int layerDefaultWidth = 400;
		int layerDefaultHeight = 300;
		int maxLayerLevel;
};

#endif /* LAYERFACTORY_H_ */
