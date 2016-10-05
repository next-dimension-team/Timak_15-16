/*
 * InteractionFragment.h
 *
 *  Created on: 27.4.2014
 *      Author: Schade
 */

#ifndef INTERACTIONFRAGMENT_H_
#define INTERACTIONFRAGMENT_H_

#include "NamedElement.h"

namespace Metamodel {

class InteractionFragment: public virtual NamedElement {
public:
	InteractionFragment();
	virtual ~InteractionFragment();
};

} /* namespace Metamodel */

#endif /* INTERACTIONFRAGMENT_H_ */
