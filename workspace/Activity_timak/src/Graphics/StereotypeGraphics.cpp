/*
 * StereotypeGraphics.cpp
 *
 *  Created on: 1.7.2013
 *      Author: Schade
 */

#include "StereotypeGraphics.h"


StereotypeGraphics::StereotypeGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm)
: ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{

}

StereotypeGraphics::~StereotypeGraphics()
{

}

Ogre::Vector3 StereotypeGraphics::getDifferenceVector()
{
	return this->differenceVector;
}

void StereotypeGraphics::setDifferenceVector(Ogre::Vector3 differenceVector)
{
	this->differenceVector = differenceVector;
}

