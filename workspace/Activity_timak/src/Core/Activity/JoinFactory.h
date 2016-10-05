#ifndef JOINFACTORY_H_
#define JOINFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;

namespace Ogre {
	class Vector2;
}

class JoinFactory: public ElementFactory {
	public:
		JoinFactory(DrawManager* drawManager);
		virtual ~JoinFactory();

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
