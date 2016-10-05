/*
 * LayerBookmarkGraphics.h
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#ifndef LAYERBOOKMARKGRAPHICS_H_
#define LAYERBOOKMARKGRAPHICS_H_

#include <string>

namespace Ogre {
	class SceneNode;
	class ManualObject;
}

class Layer;

#include "ElementGraphics.h"


class LayerBookmarkGraphics: public ElementGraphics
{
	public:
		LayerBookmarkGraphics(std::string name, Layer* layer, Ogre::ManualObject* manualObject, DrawingAlgorithm* drawingAlgorihtm);

		virtual ~LayerBookmarkGraphics();

		void setWidth(int width);
		void setHeight(int height);
		int getWidth();
		int getHeight();

	private:
		int width;
		int height;

		Ogre::SceneNode* initBeforePersist(Layer* layer, std::string name);
};

#endif /* LAYERBOOKMARKGRAPHICS_H_ */
