/*
 * Utilities.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <string>
class Element;
namespace Metamodel {
class Element;
} /* namespace Metamodel */
namespace Ogre {
class SceneNode;
} /* namespace Ogre */


class Utilities {
public:

	static Ogre::SceneNode* getSceneNode(const std::string& A_name);

	static Ogre::SceneNode* getConnectorSourceSceneNode(const std::string& A_name);
	static Ogre::SceneNode* getConnectorTargetSceneNode(const std::string& A_name);

	static Element* getConnectorSource(const std::string& A_name);
	static Element* getConnectorTarget(const std::string& A_name);


	static Element* getConnectorSource(Metamodel::Element* connectorData);
	static Element* getConnectorTarget(Metamodel::Element* connectorData);

	static Ogre::SceneNode* getConnectorSourceSceneNode(Metamodel::Element* connectorData);
	static Ogre::SceneNode* getConnectorTargetSceneNode(Metamodel::Element* connectorData);

	static Ogre::SceneNode* getSceneNode(Metamodel::Element* elem);

};

#endif /* UTILITIESDRAWING_H_ */
