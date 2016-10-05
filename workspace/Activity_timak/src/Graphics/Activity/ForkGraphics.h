#include "../ElementGraphics.h"

#ifndef FORKGRAPHICS_H_
#define FORKGRAPHICS_H_

class ForkGraphics: public ElementGraphics {
	public:
		ForkGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~ForkGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};

#endif
