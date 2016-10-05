/*
 * InteractionManager.cpp
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#include "InteractionManager.h"
#include "RaycastCommands/RaycastCommand.h"
#include <OgreCamera.h>
#include <OISMouse.h>
#include <OgreRay.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include "../Core/Container.h"
#include "../Core/Layer.h"


InteractionManager* InteractionManager::singletonObject = 0;


InteractionManager::InteractionManager() {}

InteractionManager* InteractionManager::getInstance()
{
	if (InteractionManager::singletonObject == 0) {
		singletonObject = new InteractionManager();
	}

	return singletonObject;
}

void InteractionManager::rayCast(OIS::MouseState state, RaycastCommand* command)
{
	int Swidth = this->camera->getViewport()->getActualWidth();
	int Sheight = this->camera->getViewport()->getActualHeight();

	this->ray = this->camera->getCameraToViewportRay((float) state.X.abs / Swidth, (float) state.Y.abs / Sheight);
	Ogre::RaySceneQuery* mRayScnQuery = sceneMgr->createRayQuery(ray);
	mRayScnQuery->setSortByDistance(true);

	// Execute query
	Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();

	if (command->conditionsAccepted()) {
		for (this->iter = result.begin(); this->iter != result.end(); this->iter++) {
			if (command->check()) {
				command->action();

				if (command->stop())
					break;
			}
		}
		command->postProcessAction();
	}

	mRayScnQuery->clearResults();
	sceneMgr->destroyQuery(mRayScnQuery);
}


void InteractionManager::setSceneManager(Ogre::SceneManager* sceneMgr)
{
	this->sceneMgr = sceneMgr;
}

void InteractionManager::setCamera(Ogre::Camera* camera)
{
	this->camera = camera;
}

// Deprecated: instead use: setActiveContainer()
void InteractionManager::setActiveLayer(Layer* layer)
{
	this->activeLayer = layer;
}

void InteractionManager::setActiveContainer(Container* container)
{
	this->activeContainer = container;
}

Container* InteractionManager::getActiveContainer()
{
	return this->activeContainer;
}

// Deprecated: instead use: getActiveContainer()
Layer* InteractionManager::getActiveLayer()
{
	return this->activeLayer;
}

Ogre::MovableObject* InteractionManager::getActualMovable()
{
	return this->iter->movable;
}

Ogre::RaySceneQueryResult::iterator InteractionManager::getRayResultIterator()
{
	return this->iter;
}

Ogre::Ray InteractionManager::getRay()
{
	return this->ray;
}

