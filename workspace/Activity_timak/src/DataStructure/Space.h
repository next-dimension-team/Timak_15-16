/*
 * Space.h
 *
 *  Created on: 27.4.2014
 *      Author: Schade
 */

#ifndef SPACE_H_
#define SPACE_H_

#include <vector>

#include "Layer.h"


namespace Metamodel {

class Space {
public:
	Space();
	virtual ~Space();

	void addLayer(Metamodel::Layer* layer);
	void removeLayer(Metamodel::Layer* layer);

private:
	std::vector<Metamodel::Layer*> layers;
};

} /* namespace Metamodel */

#endif /* SPACE_H_ */
