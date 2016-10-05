/*
 * NullGraphics.cpp
 *
 *  Created on: 24.6.2013
 *      Author: Schade
 */

#include "NullGraphics.h"


NullGraphics* NullGraphics::singletonObject = 0;


void NullGraphics::draw(const std::string& A_name)
{
	// nothing to draw...
}

NullGraphics::NullGraphics()
: ElementGraphics(0, 0, 0)
{

}

NullGraphics::~NullGraphics()
{

}

NullGraphics* NullGraphics::getInstance()
{
	if (NullGraphics::singletonObject == 0) {
		singletonObject = new NullGraphics();
	}

	return singletonObject;
}

