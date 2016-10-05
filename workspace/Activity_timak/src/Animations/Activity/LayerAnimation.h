/*
 * LayerAnimation.h
 *
 *  Created on: 13.1.2014
 *      Author: Schade
 */

#ifndef LAYERANIMATION_H_
#define LAYERANIMATION_H_

#include "../Animation.h"

class Layer;


class LayerAnimation : public Animation
{
	public:
		LayerAnimation(Layer* l, int depth);
		~LayerAnimation();
};

#endif /* LAYERANIMATION_H_ */
