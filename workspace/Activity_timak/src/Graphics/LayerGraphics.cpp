/*
 * LayerGraphics.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "LayerGraphics.h"

LayerGraphics::LayerGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm, int level, int width, int height)
: ElementGraphics(manualObject, sceneNode, drawingAlgorihtm)
{
	this->level =	level;
	this->width =	width;
	this->height =	height;
}

LayerGraphics::~LayerGraphics()
{

}

void LayerGraphics::setSize(int width, int height)
{
	this->width =	width;
	this->height =	height;
}

int LayerGraphics::getWidth()
{
	return this->width;
}

int LayerGraphics::getHeight()
{
	return this->height;
}

int LayerGraphics::getLevel()
{
	return this->level;
}
