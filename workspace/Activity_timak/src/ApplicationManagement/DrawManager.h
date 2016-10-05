/*
 * DrawManager.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "../Core/Association.h"
#include "../Core/Layer.h"
#include "../Graphics/DrawingAlgorithm.h"

namespace Ogre {
class ManualObject;
class SceneManager;
class SceneNode;
class Vector3;
} /* namespace Ogre */



class DrawManager
{
	public:
		static DrawManager* getInstance();

		void init(Ogre::SceneManager* sceneManager);
		Ogre::ManualObject* createManualObject(std::string name);
		Ogre::SceneNode* createChildSceneNode(std::string name, Ogre::Vector3);
		DrawingAlgorithm* getDrawingAlgorithm(std::string name);
		void setBookmarksVisibility(bool visible);
		void showLayers();
		void hideLayersExcept(Layer* layer);
		void showConnectors();
		void hideConnectorsExcept(Layer* layer);
		void redrawConnectors();
		void setVisibilityAll(bool visible);
		void showContainers(Container* container);
		void cleanUp();
		void DestroyAllAttachedMovableObjects(Ogre::SceneNode* node);
		void destroySceneNode( Ogre::SceneNode* node );
		void DrawSelectedLayers();
		void DrawNormalLayers();
		Layer* getSelectedLayer();
		void drawAll();
		void select(const std::string &A_name);
		void unselect(const std::string &A_name);
		void IncrementLayer();
		void DecrementLayer();

	private:
		static DrawManager* singletonObject;

		DrawManager();
		~DrawManager();

		Ogre::SceneManager* sceneManager;
		Ogre::SceneNode* rootSceneNode;

		std::vector<Layer*> layers;
		std::vector<Association*> connectors;
		std::map<std::string, DrawingAlgorithm*> algorithms;
};

#endif /* DRAWMANAGER_H_ */
