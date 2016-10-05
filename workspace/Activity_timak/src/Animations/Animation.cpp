/*
 * Animation.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#include "Animation.h"
#include "OgreAnimation.h"
#include <OgreLogManager.h>


int Animation::nextId = 0;


Animation::Animation() {
	this->name = generateName();
	this->length = 0;
	this->time = 0;
	this->active = true;
}

Animation::~Animation() {}


void Animation::update(double deltaTime)
{
	if (!this->active) return;
	if (this->time > this->length) {
		this->active = false;
		this->animationState->setEnabled(false);
		return;
	}

	animationState->addTime(deltaTime);
	this->time += deltaTime;
}

bool Animation::isActive()
{
	return this->active;
}

std::string Animation::generateName()
{
	std::ostringstream os;
	os << "ANIM-";
	os << Animation::nextId++;
	return os.str();
}

std::string Animation::getName()
{
	return this->name;
}
