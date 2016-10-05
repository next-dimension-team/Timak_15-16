#ifndef MERGEFACTORY_H_
#define MERGEFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;

namespace Ogre {
	class Vector2;
}

class MergeFactory: public ElementFactory{
	public:
		MergeFactory(DrawManager* drawManager);
		virtual ~MergeFactory();

		Element* factoryMethod(Container* c, Ogre::Vector2* centerPoint);

	protected:
		virtual Element* getElementInstance();
		virtual std::string getElementName();
		virtual std::string getElementType();
		virtual Metamodel::Element* getElementData();
		virtual ElementGraphics* getElementGraphics(std::string name);

	private:
		Container* container;
		Ogre::Vector2* centerPoint;
};

#endif
