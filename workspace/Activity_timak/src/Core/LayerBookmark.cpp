/*
 * LayerBookmark.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */


#include "LayerBookmark.h"

const std::string LayerBookmark::ELEMENT_TYPE = "LAYERBOOKMARK";

LayerBookmark::LayerBookmark()
{

}

LayerBookmark::~LayerBookmark()
{

}

Layer* LayerBookmark::getTarget()
{
	return this->target;
}

void LayerBookmark::setTarget(Layer* target)
{
	this->target = target;
}

