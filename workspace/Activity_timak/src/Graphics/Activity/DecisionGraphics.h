/*
 * DecisionGraphics.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef DECISIONGRAPHICS_H_
#define DECISIONGRAPHICS_H_

#include "../ElementGraphics.h"


class DecisionGraphics: public ElementGraphics
{
	public:
		DecisionGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~DecisionGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};


#endif /* DECISIONGRAPHICS_H_ */
