/*
 * LayerBookmarkFactory.cpp
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#include "LayerBookmarkFactory.h"

#include "../ApplicationManagement/DrawManager.h"
#include "../Graphics/LayerBookmarkGraphics.h"
#include "LayerBookmark.h"


LayerBookmarkFactory::LayerBookmarkFactory(DrawManager* drawManager) : ElementFactory(drawManager) {
	layer = 0;
	layerBookmark = 0;
}

LayerBookmarkFactory::~LayerBookmarkFactory() {

}

Element* LayerBookmarkFactory::factoryMethod(Layer* layer) {
	this->layer = layer;

	this->layerBookmark = static_cast<LayerBookmark*>(ElementFactory::factoryMethod());

	this->layerBookmark->setTarget(this->layer);

	return this->layerBookmark;
}

Element* LayerBookmarkFactory::getElementInstance() {
	return new LayerBookmark();
}

std::string LayerBookmarkFactory::getElementName() {
	return "layerBookmark_";
}

std::string LayerBookmarkFactory::getElementType() {
	return LayerBookmark::ELEMENT_TYPE;
}

Metamodel::Element* LayerBookmarkFactory::getElementData() {
	return 0;
}

ElementGraphics* LayerBookmarkFactory::getElementGraphics(std::string name) {
	Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(LayerBookmark::ELEMENT_TYPE);

	return new LayerBookmarkGraphics(name, this->layer, manualObject, drawingAlgorihtm);
}

