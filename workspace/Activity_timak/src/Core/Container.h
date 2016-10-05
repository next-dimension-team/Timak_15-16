/*
 * Container.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Element.h"
#include <string>
#include <vector>

namespace team4
{
class MetamodelElement;
}

class Container: public Element
{
    friend class ContainerFactory;

public:
    static const std::string ELEMENT_TYPE;

    virtual ~Container();

    void addElement(const std::pair<Element*, team4::MetamodelElement*>& elem);
    std::pair<Element*, team4::MetamodelElement*> findElement(const std::string& A_elementName);
    std::pair<Element*, team4::MetamodelElement*> findElementRecursive(const std::string& A_elementName);
    std::vector<std::pair<Element*, team4::MetamodelElement*>> getElements();

    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

protected:
    Container();

private:
    //std::vector<Element*> elements;
    std::vector<std::pair<Element*, team4::MetamodelElement*>> elements;

};


#endif /* CONTAINER_H_ */
