/*
 * AnimationManager.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef ANIMATIONMANAGER_H_
#define ANIMATIONMANAGER_H_

class Animation;


#include <vector>


class AnimationManager
{
	public:
		static AnimationManager* getInstance();

		void updateAnimations(double deltaTime);

		void addAnimation(Animation* a);

		void setNotReady();
		bool isReady();

	private:
		static AnimationManager* singletonObject;

		AnimationManager();
		~AnimationManager();

		std::vector<Animation*> animations;

		bool ready;
};

#endif /* ANIMATIONMANAGER_H_ */
