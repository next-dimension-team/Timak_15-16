#ifndef MERGEGRAPHICS_H_
#define MERGEGRAPHICS_H_

#include "../ElementGraphics.h"


class MergeGraphics: public ElementGraphics {
	public:
		MergeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~MergeGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};
#endif
