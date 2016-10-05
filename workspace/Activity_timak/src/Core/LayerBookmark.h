/*
 * LayerBookmark.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef LAYERBOOKMARK_H_
#define LAYERBOOKMARK_H_

#include <string>

#include "Element.h"

class Layer;


class LayerBookmark: public Element
{
	friend class LayerBookmarkFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~LayerBookmark();

		Layer* getTarget();
		void setTarget(Layer* target);

	private:
		Layer* target;

		LayerBookmark();
};

#endif /* LAYERBOOKMARK_H_ */
