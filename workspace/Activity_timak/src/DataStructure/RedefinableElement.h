/*
 * RedefinableElement.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef REDEFINABLEELEMENT_H_
#define REDEFINABLEELEMENT_H_

#include "NamedElement.h"

namespace Metamodel {

class RedefinableElement: public virtual NamedElement {
public:
	RedefinableElement();
	virtual ~RedefinableElement();
};

} /* namespace Metamodel */

#endif /* REDEFINABLEELEMENT_H_ */
