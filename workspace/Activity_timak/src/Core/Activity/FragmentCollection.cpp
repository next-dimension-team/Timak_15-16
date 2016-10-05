/*
 * FragmentCollection.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */


#include "FragmentCollection.h"

#include <OgreNode.h>
#include <OgreSceneNode.h>
#include <OgreVector3.h>

#include "../../Graphics/ElementGraphics.h"
#include "Fragment.h"


FragmentCollection::FragmentCollection()
{
	this->expanded = false;
}

FragmentCollection::~FragmentCollection()
{

}

Fragment* FragmentCollection::getFirst()
{
	return (fragments.size() == 0) ? 0 : fragments[0];
}

void FragmentCollection::add(Fragment* f)
{
	int size = fragments.size();
	f->getGraphics()->getSceneNode()->translate(Ogre::Vector3(0,0,-5 * size), Ogre::SceneNode::TS_PARENT);
	fragments.push_back(f);
}

std::vector<Fragment*> FragmentCollection::getAll()
{
	return fragments;
}

bool FragmentCollection::isExpanded() { return this->expanded; }
void FragmentCollection::setExpanded(bool expanded) { this->expanded = expanded; }

int FragmentCollection::getCount() { return this->fragments.size(); }
