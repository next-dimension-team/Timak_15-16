/*
 * ContainerGraphics.h
 *
 *  Created on: 14.10.2013
 *      Author: Schade
 */

#ifndef CONTAINERGRAPHICS_H_
#define CONTAINERGRAPHICS_H_

class Container;

#include "ElementGraphics.h"


class ContainerGraphics: public ElementGraphics
{
	public:
		ContainerGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm, int width = 150, int height = 100);
		virtual ~ContainerGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);

		void setSize(int width, int height);
		int getWidth();
		int getHeight();

	private:
		int width;
		int height;
};


#endif /* CONTAINERGRAPHICS_H_ */
