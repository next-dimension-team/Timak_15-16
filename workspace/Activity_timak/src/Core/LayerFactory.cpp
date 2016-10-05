/*
 * LayerFactory.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "LayerFactory.h"

#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../DataStructure/Element.h"
#include "../DataStructure/Layer.h"
#include "../Graphics/LayerGraphics.h"
#include "Layer.h"


LayerFactory::LayerFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
	resetMaxLayerLevel();
}

LayerFactory::~LayerFactory()
{

}

Element* LayerFactory::factoryMethod()
{
	return static_cast<Layer*>(ElementFactory::factoryMethod());
}

Element* LayerFactory::getElementInstance()
{
	return new Layer();
}

std::string LayerFactory::getElementName()
{
	return "layer_";
}

std::string LayerFactory::getElementType()
{
	return Layer::ELEMENT_TYPE;
}

Metamodel::Element* LayerFactory::getElementData()
{
	return new Metamodel::Layer();
}

ElementGraphics* LayerFactory::getElementGraphics(std::string name)
{
	return new LayerGraphics(
			drawManager->createManualObject(name),
			drawManager->createChildSceneNode(name, Ogre::Vector3( 0, 0, -this->maxLayerLevel * 200 )),
			drawManager->getDrawingAlgorithm(Layer::ELEMENT_TYPE),
			maxLayerLevel++,
			this->layerDefaultWidth,
			this->layerDefaultHeight
			);
}

void LayerFactory::resetMaxLayerLevel()
{
	maxLayerLevel = 1;
}
