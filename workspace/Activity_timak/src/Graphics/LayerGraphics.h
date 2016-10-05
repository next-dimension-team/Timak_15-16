/*
 * LayerGraphics.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef LAYERGRAPHICS_H_
#define LAYERGRAPHICS_H_

#include "ElementGraphics.h"
#include "../Core/Layer.h"

class OgreManualObject;

class LayerGraphics: public ElementGraphics
{
	public:
		LayerGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm, int level, int width, int height);
		virtual ~LayerGraphics();

		void setSize(int width, int height);
		int getWidth();
		int getHeight();
		int getLevel();

	private:
		int width;
		int height;
		int level;
};

#endif /* LAYERGRAPHICS_H_ */
