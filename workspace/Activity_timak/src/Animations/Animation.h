/*
 * Animation.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_


namespace Ogre {
	class Animation;
	class NodeAnimationTrack;
	class TransformKeyFrame;
	class AnimationState;
}


#include <string>


class Animation
{
	public:
		void update(double deltaTime);

		bool isActive();

	protected:
		Animation();
		~Animation();

		Ogre::Animation* animation;
		Ogre::NodeAnimationTrack* track;
		Ogre::TransformKeyFrame* key;
		Ogre::AnimationState* animationState;

		std::string getName();

		double length;
		double time;

	private:
		static int nextId;

		std::string name;
		bool active;

		static std::string generateName();
};

#endif /* ANIMATION_H_ */
