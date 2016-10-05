/*
 * Feature.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef FEATURE_H_
#define FEATURE_H_

#include "RedefinableElement.h"

namespace Metamodel {

class Feature: public RedefinableElement {
public:
	Feature();
	virtual ~Feature();
};

} /* namespace Metamodel */

#endif /* FEATURE_H_ */
