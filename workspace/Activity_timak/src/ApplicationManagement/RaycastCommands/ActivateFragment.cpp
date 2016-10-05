/*
 * ActivateFragment.cpp
 *
 *  Created on: 12.11.2013
 *      Author: Schade
 */


#include "ActivateFragment.h"

#include <OgreMovableObject.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <string>
#include <vector>

#include "../../Animations/Activity/FragmentAnimation.h"
#include "../../Animations/Activity/LayerAnimation.h"
#include "../../Core/Activity/Fragment.h"
#include "../../Core/Activity/FragmentCollection.h"
#include "../../Core/Layer.h"
#include "../../Graphics/ElementGraphics.h"
#include "../AnimationManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../InteractionManager.h"


ActivateFragment::ActivateFragment()
{

}

ActivateFragment::~ActivateFragment()
{

}

bool ActivateFragment::conditionsAccepted() {
	return true;
}

bool ActivateFragment::check() {
	return (InteractionManager::getInstance()->getActualMovable() && InteractionManager::getInstance()->getActualMovable()->getName().substr(0, 12).compare("BM_fragment_") == 0);
}

void ActivateFragment::action()
{
	if (!AnimationManager::getInstance()->isReady()) return;
	//TODO TEAM4
	/*
	Fragment* fragment = static_cast<Fragment*>(
			ElementCollection::getInstance()->findElement(
					InteractionManager::getInstance()->getActualMovable()->getName().substr(3))); // little hack possible due to naming conventions - get name without "BM_" - name of original object (instead of bookmark)

	int direction = (fragment->getFragmentCollection()->isExpanded()) ? 1 : -1;

	// animate fragments
	std::vector<Fragment*> fragments = fragment->getFragmentCollection()->getAll();
	for(unsigned int i = 1; i < fragments.size(); i++) {
		AnimationManager::getInstance()->addAnimation(new FragmentAnimation(fragments[i], 50 * i * direction));
	}

	// animate layers behind fragments
	std::vector<Layer*> layers = ElementCollection::getInstance()->getLayers();
	for(unsigned int i = 0; i < layers.size(); i++) {
		if (layers[i]->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z < fragments[0]->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO).z) {
			AnimationManager::getInstance()->addAnimation(new LayerAnimation(layers[i], 50 * (fragments.size() - 1) * direction));
		}
	}

	if (direction == 1) {
		fragment->getFragmentCollection()->setExpanded(false);
//				DrawManager::getInstance()->setVisibilityAll(true);
//				DrawManager::getInstance()->setBookmarksVisibility(false);
	} else {
		fragment->getFragmentCollection()->setExpanded(true);
//				Layer* activeLayer = ElementCollection::getInstance()->findLayerOfElement(fragment);
//				DrawManager::getInstance()->setVisibilityAll(false);
//				DrawManager::getInstance()->hideConnectorsExcept(activeLayer);
//				DrawManager::getInstance()->showContainers(activeLayer);


	}
*/
	AnimationManager::getInstance()->setNotReady(); // do not allow other animations until those are completed
}

bool ActivateFragment::stop() {
	return true;
}

void ActivateFragment::postProcessAction() {}
