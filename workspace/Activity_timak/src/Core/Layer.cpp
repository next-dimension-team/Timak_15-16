/*
 * Layer.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#include "Layer.h"
#include <typeinfo>

const std::string Layer::ELEMENT_TYPE = "LAYER";

Layer::Layer() : Container()
{

}

Layer::~Layer()
{

}

// Use addElement instead of this - this is only for backward compatibility
void Layer::addClass(Class* c)
{
	//todo team4
	//this->addElement(c);
}

// Use addElement instead of this - this is only for backward compatibility
// This is possible because name of element is unique
Class* Layer::findClass(std::string className)
{
	//todo team4
	//return static_cast<Class*>(findElement(className));
	return 0;
}

std::vector<Class*> Layer::getClasses()
{
	//todo team4
	/*std::vector<Class*> classes;

	for(unsigned int i = 0; i < this->getElements().size(); i++) {
		if (typeid(Class) == typeid(*this->getElements()[i])) {
			classes.push_back(static_cast<Class*>(this->getElements()[i]));
		}
	}

	return classes;*/

	return std::vector<Class*>(0);
}
