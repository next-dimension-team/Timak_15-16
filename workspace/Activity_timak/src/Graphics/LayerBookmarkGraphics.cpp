/*
 * LayerBookmarkGraphics.cpp
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#include "LayerBookmarkGraphics.h"
#include "../Core/LayerBookmark.h"
#include "../Core/Layer.h"
#include "../Graphics/LayerGraphics.h"
#include <OgreSceneNode.h>


LayerBookmarkGraphics::LayerBookmarkGraphics(std::string name, Layer* layer, Ogre::ManualObject* manualObject, DrawingAlgorithm* drawingAlgorihtm)
: ElementGraphics(manualObject, initBeforePersist(layer, name), drawingAlgorihtm)
{

}

LayerBookmarkGraphics::~LayerBookmarkGraphics()
{

}


Ogre::SceneNode* LayerBookmarkGraphics::initBeforePersist(Layer* layer, std::string name)
{
	this->width = 30;
	this->height = 20;

	Ogre::Vector3* centerPoint = new Ogre::Vector3(
		layer->getGraphics()->getSceneNode()->getPosition().x +
			static_cast<LayerGraphics*>(layer->getGraphics())->getWidth() / 2 +
			this->width / 2,
		layer->getGraphics()->getSceneNode()->getPosition().y +
			static_cast<LayerGraphics*>(layer->getGraphics())->getHeight() / 2 -
			this->height / 2 -
			this->height *
			static_cast<LayerGraphics*>(layer->getGraphics())->getLevel(),
		0);

	return layer->getGraphics()->getSceneNode()->createChildSceneNode(name + "_node", *centerPoint);
}

void LayerBookmarkGraphics::setWidth(int width)
{
	this->width = width;
}

void LayerBookmarkGraphics::setHeight(int height)
{
	this->height = height;
}

int LayerBookmarkGraphics::getWidth()
{
	return this->width;
}

int LayerBookmarkGraphics::getHeight()
{
	return this->height;
}
