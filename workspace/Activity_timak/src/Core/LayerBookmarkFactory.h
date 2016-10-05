/*
 * LayerBookmarkFactory.h
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#ifndef LAYERBOOKMARKFACTORY_H_
#define LAYERBOOKMARKFACTORY_H_

#include <string>

#include "ElementFactory.h"

class Layer;
class LayerBookmark;


class LayerBookmarkFactory: public ElementFactory
{
	public:
		LayerBookmarkFactory(DrawManager* drawManager);
		virtual ~LayerBookmarkFactory();

		Element* factoryMethod(Layer* layer);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

		Element* factoryMethod();

	private:
		Layer* layer;
		LayerBookmark* layerBookmark;
};

#endif /* LAYERBOOKMARKFACTORY_H_ */
