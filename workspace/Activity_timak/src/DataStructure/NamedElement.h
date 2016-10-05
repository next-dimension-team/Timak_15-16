/*
 * NamedElement.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef NAMEDELEMENT_H_
#define NAMEDELEMENT_H_

#include <string>

#include "Element.h"


namespace Metamodel {

class NamedElement: public virtual Metamodel::Element {
public:
	NamedElement();
	virtual ~NamedElement();

	std::string getName();
	void setName(std::string name);

private:
	std::string name;
};

} /* namespace Metamodel */

#endif /* NAMEDELEMENT_H_ */
