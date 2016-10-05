/*
 * ActivityFragment.cpp
 *
 *  Created on: 28.4.2014
 *      Author: Schade
 */

#include "ActivityFragment.h"

#include <iterator>

#include "ActivityNode.h"

namespace Metamodel {

ActivityFragment::ActivityFragment() {
	this->fragmentCondition = "";
	this->fragmentType = "";
}

ActivityFragment::~ActivityFragment() {
	// TODO Auto-generated destructor stub
}

std::string ActivityFragment::getFragmentCondition()
{
	return this->fragmentCondition;
}

std::string ActivityFragment::getFragmentType()
{
	return this->fragmentType;
}

void ActivityFragment::setFragmentCondition(std::string fragmentCondition)
{
	this->fragmentCondition = fragmentCondition;
}

void ActivityFragment::setFragmentType(std::string fragmentType)
{
	this->fragmentType = fragmentType;
}

void ActivityFragment::addElement(Metamodel::ActivityNode* e)
{
	this->elements.push_back(e);
}

std::vector<Metamodel::ActivityNode*> ActivityFragment::getElements()
{
	return this->elements;
}

bool ActivityFragment::containsElement(Metamodel::ActivityNode* searched) {
	for(std::vector<Metamodel::ActivityNode*>::iterator i = elements.begin(); i != elements.end(); i++) {
		if (searched == *i) {
			return true;
		}
	}
	return false;
}

} /* namespace Metamodel */
