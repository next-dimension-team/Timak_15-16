/*
 * FragmentGraphics.cpp
 *
 *  Created on: 25.11.2013
 *      Author: Schade
 */

#include "FragmentGraphics.h"
#include "../../HelperTeam4.h"

#include <OgreVector3.h>

FragmentGraphics::FragmentGraphics(Ogre::ManualObject* manualObject,
                                   Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm,
                                   Ogre::ManualObject* bookmarkManualObject, int width, int height) :
        ContainerGraphics(manualObject, sceneNode, drawingAlgorihtm, width,
                          height)
{
    this->bookmarkManualObject = bookmarkManualObject;
}

FragmentGraphics::~FragmentGraphics()
{}

Ogre::ManualObject* FragmentGraphics::getBookmarkManualObject()
{
    return this->bookmarkManualObject;
}

Ogre::Vector3 FragmentGraphics::getConnectorBeginPoint(const std::string& A_name)
{
	DEF_BEGIN;
    return ContainerGraphics::getConnectorBeginPoint(A_name);
}

Ogre::Vector3 FragmentGraphics::getConnectorEndPoint(const std::string& A_name)
{
    return ContainerGraphics::getConnectorEndPoint(A_name);
}
