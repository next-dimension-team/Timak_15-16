/*
 * StereotypeGraphics.h
 *
 *  Created on: 1.7.2013
 *      Author: Schade
 */

#ifndef STEREOTYPEGRAPHICS_H_
#define STEREOTYPEGRAPHICS_H_


#include <OgreVector3.h>

#include "ElementGraphics.h"

namespace Ogre {
class ManualObject;
class SceneNode;
} /* namespace Ogre */


class StereotypeGraphics: public ElementGraphics
{
	public:
		StereotypeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~StereotypeGraphics();

		void setDifferenceVector(Ogre::Vector3 differenceVector);
		Ogre::Vector3 getDifferenceVector();

	private:
		Ogre::Vector3 differenceVector;
};


#endif /* STEREOTYPEGRAPHICS_H_ */
