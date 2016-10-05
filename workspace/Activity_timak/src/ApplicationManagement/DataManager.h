/*
 * DataManager.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_

#include <string>

namespace Ogre {
	class Vector2;
}


class Layer;
class Class;
class Method;
class Attribute;
class Association;
class Generalisation;
class Aggregation;
class Stereotype;
class Fragment;
class Container;

#include <map>
#include "../Core/ElementFactory.h"
#include <vector>

class DataManager {
	public:
		static DataManager* getInstance();

		Layer* createLayer();
		Class* createClass(Layer* lay, std::string className, Ogre::Vector2* centerPoint);
		void createMethod(Class* cla, std::string methodName);
		void createAttribute(Class* cla, std::string attributeName);
		Association* createAssociation(Class* source, Class* target);
		Aggregation* createAggregation(Class* source, Class* target);
		Generalisation* createGeneralisation(Class* source, Class* target);
		Stereotype* setNewStereotype(Association* ass, std::string stereotypeName);
		Stereotype* setNewStereotype(Aggregation* agg, std::string stereotypeName);

		Element* createActivity(Container* c, std::string activityName, Ogre::Vector2* centerPoint);
		Element* createDecision(Container* c, Ogre::Vector2* centerPoint);
		Element* createMerge(Container* c, Ogre::Vector2* centerPoint);
		Element* createFork(Container* c, Ogre::Vector2* centerPoint);
		Element* createJoin(Container* c, Ogre::Vector2* centerPoint);
		Element* createFlow(const std::string& sourceName, const std::string& targetName, const std::string& A_text = "");
		Element* createInitialNode(Container* c, Ogre::Vector2* centerPoint);
		Element* createFinalNode(Container* c, Ogre::Vector2* centerPoint);
		Element* createLoop(Container* c, Ogre::Vector2* centerPoint, const std::string& A_init, const std::string& A_cond, int width = 150, int height = 100);
		Element* createAlt(Container* c, Ogre::Vector2* centerPoint, const std::vector<std::string>& A_condition,int width = 150, int height = 100);

		Container* createContainer(Element* elem, Ogre::Vector2* centerPoint);
		Element* createFragment(Container* c, Ogre::Vector2* centerPoint, int width = 150, int height = 100);

		void resetFactories();

	private:
		static DataManager* singletonObject;

		DataManager();
		~DataManager();

		std::map<std::string, ElementFactory*> factories;
};

#endif
