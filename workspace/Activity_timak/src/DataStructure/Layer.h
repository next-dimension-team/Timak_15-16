/*
 * Layer.h
 *
 *  Created on: 27.4.2014
 *      Author: Schade
 */

#ifndef LAYER_METAMODEL_H_
#define LAYER_METAMODEL_H_

#include <vector>

#include "NamedElement.h"


namespace Metamodel {

class Layer: public Metamodel::NamedElement {
public:
	Layer();
	virtual ~Layer();

	void addElement(Metamodel::NamedElement* e);
	std::vector<Metamodel::NamedElement*> getElements();
	bool containsElement(Metamodel::NamedElement* searched);

private:
	std::vector<Metamodel::NamedElement*> elements;
};

} /* namespace Metamodel */

#endif /* LAYER_H_ */
