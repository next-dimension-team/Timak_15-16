/*
 * Class.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef CLASS_METAMODEL_H_
#define CLASS_METAMODEL_H_

#include <vector>

#include "Classifier.h"
#include "Operation.h"
#include "Property.h"

namespace Metamodel {

class Class: public Classifier {
public:
	Class();
	virtual ~Class();

	void addOperation(Operation* o);
	void removeOperation(Operation* o);
	std::vector<Operation*> getOperations();

	void addAttribute(Property* p);
	void removeAttribute(Property* p);
	std::vector<Property*> getAttributes();

private:
	std::vector<Operation*> ownedOperation;
	std::vector<Property*> ownedAttribute;
};

} /* namespace Metamodel */

#endif /* CLASS_METAMODEL_H_ */
