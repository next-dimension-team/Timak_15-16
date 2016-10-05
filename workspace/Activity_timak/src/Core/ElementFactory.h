/*
 * ElementFactory.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ELEMENTFACTORY_H_
#define ELEMENTFACTORY_H_

#include <string>

class DrawManager;
class Element;
class ElementGraphics;
namespace Metamodel
{
class Element;
} /* namespace Metamodel */


class ElementFactory
{
public:
    ElementFactory(DrawManager* drawManager);
    virtual ~ElementFactory();

protected:
    DrawManager* drawManager;

    virtual Element* getElementInstance();
    virtual std::string getElementName();
    virtual std::string getElementType();
    virtual Metamodel::Element* getElementData();
    virtual ElementGraphics* getElementGraphics(std::string name);

    Element* factoryMethod();

private:
    int maxId;

    int idManager();
    Element* createElement();
    Element* initializeElement(Element*);
    Element* assignElementData(Element*);
    Element* assignElementGraphics(Element*);
};

#endif /* ELEMENTFACTORY_H_ */
