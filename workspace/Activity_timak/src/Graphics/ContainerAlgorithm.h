/*
 * ContainerAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef CONTAINERALGORITHM_H_
#define CONTAINERALGORITHM_H_

#include "DrawingAlgorithm.h"

class Container;
class ContainerGraphics;

class ContainerAlgorithm: public DrawingAlgorithm {
public:
	ContainerAlgorithm();
	virtual ~ContainerAlgorithm();

	virtual void draw(const std::string& A_name);

private:
	Container* elem;
	ContainerGraphics* elemGraphics;
};

#endif /* CONTAINERALGORITHM_H_ */
