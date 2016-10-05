/*
 * Fragment.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */


#include "Fragment.h"

#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>

#include "FragmentCollection.h"


const std::string Fragment::ELEMENT_TYPE = "Fragment";

Fragment::Fragment() : Container() {
	this->fragmentCollection = 0;
}
Fragment::~Fragment() {
	Ogre::MaterialManager::getSingleton().remove(getName() + "Bookmark_material");
	Ogre::MaterialManager::getSingleton().remove(getName() + "Type_material");
	Ogre::MaterialManager::getSingleton().remove(getName() + "Condition_material");
	Ogre::TextureManager::getSingleton().remove(getName() + "Bookmark_texture");
	Ogre::TextureManager::getSingleton().remove(getName() + "Type_texture");
	Ogre::TextureManager::getSingleton().remove(getName() + "Condition_texture");
}

FragmentCollection* Fragment::getFragmentCollection()
{
	return this->fragmentCollection;
}

int Fragment::getCollectionFragmentsCount()
{
	return this->fragmentCollection->getCount();
}
