/*
 * FragmentFactory.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef FRAGMENTFACTORY_H_
#define FRAGMENTFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;
class Fragment;
class FragmentCollection;
namespace Ogre {
class Vector2;
} /* namespace Ogre */


class FragmentFactory: public ElementFactory
{
	public:
		FragmentFactory(DrawManager* drawManager);
		virtual ~FragmentFactory();

		Element* factoryMethod(Container* c, Ogre::Vector2* centerPoint,int width = 150, int height = 100);
		//team4::MetamodelElement* factoryMethodTeam4(Container* c, Ogre::Vector2* centerPoint, std::string fragmentType, std::string fragmentCondition, team4::StructuredActivityNode* f = 0);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Container* container;
		Ogre::Vector2* centerPoint;
		FragmentCollection* fragmentCollection;
		int width;
		int height;

		std::string fragmentType;
		std::string fragmentCondition;
};

#endif /* FRAGMENTFACTORY_H_ */
