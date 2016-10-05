/*
 * ClassGraphics.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef CLASSGRAPHICS_H_
#define CLASSGRAPHICS_H_

class Class;

#include "ElementGraphics.h"


class ClassGraphics: public ElementGraphics
{
	public:
		ClassGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~ClassGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};

#endif /* CLASSGRAPHICS_H_ */
