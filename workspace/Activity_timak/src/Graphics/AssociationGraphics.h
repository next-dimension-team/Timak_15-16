/*
 * AssociationGraphics.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ASSOCIATIONGRAPHICS_H_
#define ASSOCIATIONGRAPHICS_H_

#include "ElementGraphics.h"

class AssociationGraphics: public ElementGraphics
{
	public:
		AssociationGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
		virtual ~AssociationGraphics();

		void virtual draw(const std::string& A_name);
		double getLength();
};

#endif /* ASSOCIATIONGRAPHICS_H_ */
