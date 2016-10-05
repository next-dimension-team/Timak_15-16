/*
 * Association.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef ASSOCIATION_METAMODEL_H_
#define ASSOCIATION_METAMODEL_H_

#include <string>
#include <vector>

#include "Classifier.h"
#include "Property.h"
#include "Relationship.h"


namespace Metamodel {

class Association: public Relationship, public Classifier {
public:
	Association();
	virtual ~Association();

	void addMemberEnd(Metamodel::Property* p);
	std::vector<Property*> getMemberEnds();

	std::string getStereotype();
	void setStereotype(std::string s);

private:
	std::vector<Property*> memberEnd;
	std::string stereotype; // FIXME: where is stereotype in metamodel?!
};

} /* namespace Metamodel */

#endif /* ASSOCIATION_METAMODEL_H_ */
