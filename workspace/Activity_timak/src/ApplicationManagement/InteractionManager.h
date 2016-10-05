/*
 * InteractionManager.h
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#ifndef INTERACTIONMANAGER_H_
#define INTERACTIONMANAGER_H_

namespace Ogre {
	class SceneManager;
	class Camera;
	class MovableObject;
	class Ray;
}

namespace OIS {
	class MouseState;
}

class Layer;
class RaycastCommand;
class Container;

#include <OgreSceneQuery.h>


class InteractionManager
{
	public:
		static InteractionManager* getInstance();

		void setSceneManager(Ogre::SceneManager* sceneMgr);
		void setCamera(Ogre::Camera* camera);
		void setActiveLayer(Layer* layer);
		Layer* getActiveLayer();
		void setActiveContainer(Container* container);
		Container* getActiveContainer();
		Ogre::MovableObject* getActualMovable();
		Ogre::Ray getRay();
		Ogre::RaySceneQueryResult::iterator getRayResultIterator();

		void rayCast(OIS::MouseState state, RaycastCommand* command);

	private:
		static InteractionManager* singletonObject;

		InteractionManager();
		~InteractionManager();

		Container* activeContainer;
		Layer* activeLayer;
		Ogre::Ray ray;
		Ogre::RaySceneQueryResult::iterator iter;

		Ogre::SceneManager* sceneMgr;
		Ogre::Camera* camera;
};

#endif /* INTERACTIONMANAGER_H_ */
