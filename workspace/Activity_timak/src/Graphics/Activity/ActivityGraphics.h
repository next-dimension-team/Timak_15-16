/*
 * ActivityGraphics.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef ACTIVITYGRAPHICS_H_
#define ACTIVITYGRAPHICS_H_

#include "../ElementGraphics.h"

namespace Ogre {
class Font;
} /* namespace Ogre */


class ActivityGraphics: public ElementGraphics
{
	public:
		ActivityGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~ActivityGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};

#endif /* ACTIVITYGRAPHICS_H_ */
