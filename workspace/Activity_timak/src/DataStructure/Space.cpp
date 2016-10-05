/*
 * Space.cpp
 *
 *  Created on: 27.4.2014
 *      Author: Schade
 */

#include "Space.h"

#include <algorithm>
#include <iterator>


namespace Metamodel {

Space::Space() {
	// TODO Auto-generated constructor stub
}

Space::~Space() {
	// TODO Auto-generated destructor stub
}

void Space::addLayer(Metamodel::Layer* layer) {
	this->layers.push_back(layer);
}

void Space::removeLayer(Metamodel::Layer* layer) {
	this->layers.erase(std::remove(this->layers.begin(), this->layers.end(), layer), this->layers.end());
}

} /* namespace Metamodel */
