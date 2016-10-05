/*
 * AnimationManager.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#include "AnimationManager.h"
#include "../Animations/Animation.h"
#include <OgreLogManager.h>

#include "../ApplicationManagement/DrawManager.h"


AnimationManager* AnimationManager::singletonObject = 0;


AnimationManager::AnimationManager() {
	this->ready = true;
}

AnimationManager::~AnimationManager() {}


AnimationManager* AnimationManager::getInstance()
{
	if (AnimationManager::singletonObject == 0) {
		singletonObject = new AnimationManager();
	}

	return singletonObject;
}


void AnimationManager::updateAnimations(double deltaTime)
{
	std::vector<Animation*>::iterator i = this->animations.begin();
	while(i != this->animations.end()) {
		if(!(*i)->isActive()) {
			i = this->animations.erase(i);
		} else {
			(*i)->update(deltaTime);
			i++;
		}
	}

	if (this->animations.size() > 0) {
		// TODO: check performance - if it is slow then redraw only on animation end
		DrawManager::getInstance()->redrawConnectors(); // redrawing during animation
	} else if (this->animations.size() == 0 && !this->ready) {
		this->ready = true;
		DrawManager::getInstance()->redrawConnectors(); // redrawing on animation end
	}


}

void AnimationManager::addAnimation(Animation* a)
{
	if (this->ready) this->animations.push_back(a);
}

void AnimationManager::setNotReady()
{
	this->ready = false;
}

bool AnimationManager::isReady()
{
	return this->ready;
}
