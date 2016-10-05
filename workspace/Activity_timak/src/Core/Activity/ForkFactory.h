#ifndef FORKFACTORY_H_
#define FORKFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;

namespace Ogre {
	class Vector2;
}

class ForkFactory: public ElementFactory {
	public:
		ForkFactory(DrawManager* drawManager);
		virtual ~ForkFactory();

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
