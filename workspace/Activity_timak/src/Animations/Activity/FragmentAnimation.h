/*
 * FragmentAnimation.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef FRAGMENTANIMATION_H_
#define FRAGMENTANIMATION_H_

#include "../Animation.h"

class Fragment;


class FragmentAnimation : public Animation
{
	public:
		FragmentAnimation(Fragment* f, int depth);
		~FragmentAnimation();
};

#endif /* FRAGMENTANIMATION_H_ */
