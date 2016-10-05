/*
 * Element.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "../DataStructure/Element.h"
#include "Element.h"

#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>

#include "../Graphics/ElementGraphics.h"
#include "../HelperTeam4.h"


Element::Element()
{
	selected_layer = false;
    selected = false;
    data = 0;
    graphics = 0;
    id = 0;
    drawing = false;
}
void Element::Log()
{
    std::cout <<  "LOG_ELEMENT  Id " << id << " name " << name  << " type " << type << std::endl;

}


Element::~Element()
{
    delete data;
    delete graphics;
    Ogre::MaterialManager::getSingleton().remove(getName() + "_material");
    Ogre::TextureManager::getSingleton().remove(getName() + "_texture");
}


void Element::setLayerSelect(bool state)
{
    if (state)
        selected_layer = true;
    else
        selected_layer = false;
}

bool Element::getLayerSelect()
{
    return selected_layer;
}

void Element::select()
{
    graphics->select(this);
}

void Element::unselected()
{
    graphics->unselected(this);
}

void Element::setSelect()
{
    selected=true;
}

void Element::unsetSelect()
{
    selected=false;
}

bool Element::getSelect()
{
    return this->selected;
}

int Element::getId()
{
    return this->id;
}

void Element::setId(int id)
{
    this->id = id;
}

Ogre::Vector2* Element::getCenter()
{
    return centerPoint;
}

void Element::setCenter(Ogre::Vector2* centerPoint)
{
    this->centerPoint = centerPoint;
}

std::string Element::getLayer()
{
    return layer;
}

void Element::setLayer(std::string name)
{
    this->layer = name;
}

std::string Element::getName()
{
    return this->name;
}

void Element::setName(std::string name)
{
    this->name = name;
}

Metamodel::Element* Element::getData()
{
    return this->data;
}
void Element::setData(Metamodel::Element* data)
{
    this->data = data;
}

ElementGraphics* Element::getGraphics()
{
    return this->graphics;
}

void Element::setGraphics(ElementGraphics* graphics)
{
    DEF_BEGIN;
    this->graphics = graphics;
}

std::string Element::getType()
{
    return this->type;
}

void Element::setType(std::string type)
{
    this->type = type;
}

void Element::draw(const std::string& A_name)
{
    DEF_BEGIN;
    if (graphics != NULL)
    {
        this->graphics->draw(A_name);
    }
    else
    {
        DEF_ERROR("graphics is NULL");
    }
}

Element* Element::clone()
{
    Element *temp = new Element();
    temp->id = this->id;
    temp->name = this->name;
    temp->type = this->type;

    return temp;
}

bool Element::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
    	DEF_WRITE2FILE3(A_stream, drawing, selected, selected_layer);

        if (centerPoint != NULL)
        {
        	DEF_WRITE2FILE2(A_stream, centerPoint->x, centerPoint->y);
        }
        else
        {
            DEF_ERROR("centerPoint is NULL");
            DEF_WRITE2FILE2(A_stream, 0, 0);
        }
        if (graphics != NULL)
        {
            graphics->serialization(A_stream);
        }
        else
        {
            DEF_ERROR("graphics is NULL");
            return false;
        }
        return true;
    }
    DEF_ERROR("ofstream is not opened!");
    return false;
}
bool Element::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
    	DEF_READFROMFILE3(A_stream, drawing, selected, selected_layer);
        int x,y;
        DEF_READFROMFILE2(A_stream, x, y);
        A_stream >> x >> y;
        centerPoint = new Ogre::Vector2(x, y);

        //graphics
        /*int sizeContour;
        A_stream >> sizeContour;
        contour.resize(0);
        contour.reserve(sizeContour);
        int x, y;
        for (int i = 0; i < sizeContour; i++)
    {
        	A_stream >> x >> y;
        	contour.push_back(cv::Point(x, y));
    }
        A_stream >> centerPoint.x >> centerPoint.y;
        A_stream >> _inObject;
        A_stream >> id;*/
        return true;
    }
    return false;
}

