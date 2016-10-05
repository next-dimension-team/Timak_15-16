/*
 * NodeGraphics.h
 *
 *  Created on: 21.10.2013
 *      Author: Schade
 */

#ifndef NODEGRAPHICS_H_
#define NODEGRAPHICS_H_

#include "../ElementGraphics.h"

class NodeGraphics: public ElementGraphics
{
	public:
		NodeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~NodeGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};

#endif /* NODEGRAPHICS_H_ */
