/*
 * FlowGraphics.h
 *
 *  Created on: 17.10.2013
 *      Author: Schade
 */

#ifndef FLOWGRAPHICS_H_
#define FLOWGRAPHICS_H_

#include "../ElementGraphics.h"

class FlowGraphics: public ElementGraphics
{
	public:
		FlowGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~FlowGraphics();

		void virtual draw(const std::string& A_name);
		double getLength();
};


#endif /* FLOWGRAPHICS_H_ */
