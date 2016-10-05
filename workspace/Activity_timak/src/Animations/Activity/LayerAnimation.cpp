/*
 * LayerAnimation.cpp
 *
 *  Created on: 13.1.2014
 *      Author: Schade
 */

#include "LayerAnimation.h"

#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../../Core/Layer.h"
#include "../../Graphics/ElementGraphics.h"
#include "../../Main.h"


LayerAnimation::LayerAnimation(Layer* l, int depth) : Animation()
{
	if (Main::sMSceneMgr->hasAnimationState(this->getName())) Main::sMSceneMgr->destroyAnimationState(this->getName());
	if (Main::sMSceneMgr->hasAnimation(this->getName())) Main::sMSceneMgr->destroyAnimation(this->getName());

	Ogre::SceneNode* node = l->getGraphics()->getSceneNode();
	Ogre::Vector3 start = node->getPosition();

	this->length = 2;

	animation = Main::sMSceneMgr->createAnimation(this->getName(), this->length);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);

	track = this->animation->createNodeTrack(1, node);

	key = track->createNodeKeyFrame(0);
	key->setTranslate(start);

	key = track->createNodeKeyFrame(1);
	key->setTranslate(Ogre::Vector3(start.x,start.y,start.z+depth/5*4));

	key = track->createNodeKeyFrame(2);
	key->setTranslate(Ogre::Vector3(start.x,start.y,start.z+depth));

	animationState = Main::sMSceneMgr->createAnimationState(this->getName());

	animationState->setLoop(false);
	animationState->setEnabled(true);
}

LayerAnimation::~LayerAnimation() {}