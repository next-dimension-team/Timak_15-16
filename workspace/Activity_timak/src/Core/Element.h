/*
 * Element.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ELEMENT_CORE_H_
#define ELEMENT_CORE_H_

#include <string>
#include <OgreManualObject.h>
#include "../HelperTeam4.h"
#include "../Graphics/ElementGraphics.h"
#include <string>
#include <fstream>
namespace Metamodel
{
class Element;
} /* namespace Metamodel */

namespace Ogre
{
class Vector2;
}

//class ElementGraphics;

class Element
{
    friend class ElementFactory;

public:
    bool drawing;
    bool selected;
    bool selected_layer;
    Ogre::MaterialPtr material;
    virtual ~Element();
    void select();
    void unselected();
    ElementGraphics* getGraphics();
    void setId(int id);
    void setSelect();
    void unsetSelect();
    bool getSelect();

    void setLayerSelect(bool state);
    bool getLayerSelect();
    void setCenter(Ogre::Vector2* centerPoint);
    void setLayer(std::string name);
    Ogre::Vector2* getCenter();
    void setData(Metamodel::Element* data);
    void setGraphics(ElementGraphics* graphics);

    void draw(const std::string& A_name);
    Element* clone();
    void Log();


    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
    Metamodel::Element* getData();
    std::string getType();
    void setName(std::string name);
    int getId();
    std::string getName();
    std::string getLayer();

protected:




    int id;
    std::string name;
    Metamodel::Element* data;
    ElementGraphics* graphics;
    std::string type;
    std::string layer;

    Element();

private:
    void setType(std::string type);
    Ogre::Vector2* centerPoint = NULL;
};

#endif /* ELEMENT_CORE_H_ */
