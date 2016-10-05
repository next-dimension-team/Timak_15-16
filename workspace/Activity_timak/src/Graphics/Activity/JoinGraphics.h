#include "../ElementGraphics.h"
#include <string>
#ifndef JoinGRAPHICS_H_
#define JoinGRAPHICS_H_

class JoinGraphics: public ElementGraphics {
	public:
		JoinGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~JoinGraphics();

		Ogre::Vector3 getConnectorBeginPoint(const std::string& A_name);
		Ogre::Vector3 getConnectorEndPoint(const std::string& A_name);
};

#endif
