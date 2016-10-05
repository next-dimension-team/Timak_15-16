/*
 * LayerBookmarkAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef LAYERBOOKMARKALGORITHM_H_
#define LAYERBOOKMARKALGORITHM_H_

#include "DrawingAlgorithm.h"

class LayerBookmarkAlgorithm: public DrawingAlgorithm {
public:
	LayerBookmarkAlgorithm();
	virtual ~LayerBookmarkAlgorithm();

	virtual void draw(const std::string& A_name);
	virtual void select(Element* elem);
	virtual void unselected(Element* elem);
};

#endif /* LAYERBOOKMARKALGORITHM_H_ */
