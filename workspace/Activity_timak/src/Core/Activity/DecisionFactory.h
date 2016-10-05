/*
 * DecisionFactory.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef DECISIONFACTORY_H_
#define DECISIONFACTORY_H_

#include <string>

#include "../ElementFactory.h"

class Container;
namespace Ogre
{
class Vector2;
} /* namespace Ogre */


class DecisionFactory: public ElementFactory
{
public:
    DecisionFactory(DrawManager* drawManager);
    virtual ~DecisionFactory();

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


#endif /* DECISIONFACTORY_H_ */
