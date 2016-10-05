/*
 * Generalization.h
 *
 *  Created on: 11.4.2014
 *      Author: Schade
 */

#ifndef GENERALIZATION_H_
#define GENERALIZATION_H_

#include "DirectedRelationship.h"

namespace Metamodel {
class Classifier;
} /* namespace Metamodel */

namespace Metamodel {

class Generalization: public DirectedRelationship {
public:
	Generalization();
	virtual ~Generalization();

	Classifier* getGeneral();
	void setGeneral(Classifier* general);
	Classifier* getSpecific();
	void setSpecific(Classifier* specific);

private:
	Classifier* general;
	Classifier* specific;
};

} /* namespace Metamodel */

#endif /* GENERALIZATION_H_ */
