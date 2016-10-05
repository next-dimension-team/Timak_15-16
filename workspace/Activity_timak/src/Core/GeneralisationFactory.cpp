/*
 * GeneralisationFactory.cpp
 *
 *  Created on: 17.6.2013
 *      Author: Schade
 */

#include "GeneralisationFactory.h"

#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../ApplicationManagement/DrawManager.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/Generalization.h"
#include "../Graphics/AssociationGraphics.h"
#include "Class.h"
#include "Generalisation.h"
#include "Utilities.h"


GeneralisationFactory::GeneralisationFactory(DrawManager* drawManager) : ElementFactory(drawManager)
{
	this->source = 0;
	this->target = 0;
}

GeneralisationFactory::~GeneralisationFactory()
{

}

Element* GeneralisationFactory::factoryMethod(Class* source, Class* target)
{
	return factoryMethod(dynamic_cast<Metamodel::Class*>(source->getData()), dynamic_cast<Metamodel::Class*>(target->getData()));
}

Element* GeneralisationFactory::factoryMethod(Metamodel::Class* source, Metamodel::Class* target)
{
	this->source = source;
	this->target = target;

	return ElementFactory::factoryMethod();
}

Element* GeneralisationFactory::getElementInstance()
{
	return new Generalisation();
}

std::string GeneralisationFactory::getElementName()
{
	return "generalisation_";
}

std::string GeneralisationFactory::getElementType()
{
	return Generalisation::ELEMENT_TYPE;
}

Metamodel::Element* GeneralisationFactory::getElementData()
{
	Metamodel::Generalization* elemData = new Metamodel::Generalization();

	elemData->setSpecific(source);
	elemData->setGeneral(target);

	return elemData;
}

ElementGraphics* GeneralisationFactory::getElementGraphics(std::string name)
{
	/*Ogre::ManualObject* manualObject = drawManager->createManualObject(name);
	Ogre::SceneNode* sceneNode = Utilities::getSceneNode(this->source)->createChildSceneNode(name + "_node", Ogre::Vector3::ZERO);
	DrawingAlgorithm* drawingAlgorihtm = drawManager->getDrawingAlgorithm(Generalisation::ELEMENT_TYPE);

	return new AssociationGraphics(manualObject, sceneNode, drawingAlgorihtm);*/
	return 0;
}
