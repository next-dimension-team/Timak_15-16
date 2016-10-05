/*
 * FragmentGraphics.h
 *
 *  Created on: 25.11.2013
 *      Author: Schade
 */

#ifndef FRAGMENTGRAPHICS_H_
#define FRAGMENTGRAPHICS_H_

#include "../ContainerGraphics.h"

class FragmentGraphics: public ContainerGraphics {
public:
	FragmentGraphics(Ogre::ManualObject* manualObject,
			Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm,
			Ogre::ManualObject* bookmarkManualObject, int width = 150,
			int height = 100);
	virtual ~FragmentGraphics();

	Ogre::ManualObject* getBookmarkManualObject();

	Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
	Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);

private:
	Ogre::ManualObject* bookmarkManualObject;
};

#endif /* FRAGMENTGRAPHICS_H_ */
