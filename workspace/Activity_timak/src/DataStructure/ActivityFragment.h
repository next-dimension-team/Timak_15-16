/*
 * ActivityFragment.h
 *
 *  Created on: 28.4.2014
 *      Author: Schade
 */

#ifndef ACTIVITYFRAGMENT_H_
#define ACTIVITYFRAGMENT_H_

#include <string>
#include <vector>

#include "ActivityNode.h"
#include "InteractionFragment.h"

namespace Metamodel {

class ActivityFragment: public Metamodel::InteractionFragment, public Metamodel::ActivityNode {
public:
	ActivityFragment();
	virtual ~ActivityFragment();

	void addElement(Metamodel::ActivityNode* e);
	std::vector<Metamodel::ActivityNode*> getElements();
	bool containsElement(Metamodel::ActivityNode* searched);

	std::string getFragmentCondition();
	std::string getFragmentType();

	void setFragmentCondition(std::string fragmentCondition);
	void setFragmentType(std::string fragmentType);

private:
	std::vector<Metamodel::ActivityNode*> elements;
	std::string fragmentCondition;
	std::string fragmentType;
};

} /* namespace Metamodel */

#endif /* ACTIVITYFRAGMENT_H_ */
