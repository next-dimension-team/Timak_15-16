#include "ElementGraphics.h"
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include "DrawingAlgorithm.h"
#include "../HelperTeam4.h"

void ElementGraphics::select(Element* elem)
{
    drawingAlgorihtm->select(elem);
}

ElementGraphics::ElementGraphics(Ogre::ManualObject* manualObject, Ogre::SceneNode* node, DrawingAlgorithm* drawingAlgorihtm)
{
    this->manualObject = manualObject;
    this->node = node;
    this->drawingAlgorihtm = drawingAlgorihtm;
}

ElementGraphics::~ElementGraphics()
{}

void ElementGraphics::draw(const std::string& A_name)
{
	DEF_BEGIN;
	if (drawingAlgorihtm != NULL)
	{
		drawingAlgorihtm->draw(A_name);
	}
	else
	{
		DEF_ERROR("drawingAlgorihtm is NULL");
	}
}

void ElementGraphics::unselected(Element* elem)
{

    drawingAlgorihtm->unselected(elem);
}

Ogre::SceneNode* ElementGraphics::getSceneNode()
{
    return this->node;
}

Ogre::ManualObject* ElementGraphics::getManualObject()
{
    return this->manualObject;
}

Ogre::Vector3 ElementGraphics::getConnectorBeginPoint(const std::string& A_name)
{
	DEF_BEGIN;
    return this->node->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
}

Ogre::Vector3 ElementGraphics::getConnectorEndPoint(const std::string& A_name)
{
    return this->node->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
}

bool ElementGraphics::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        /*A_stream << drawing << "\t" << selected << "\t" <<  selected_layer << "\t" << "\n";

        if (centerPoint != NULL)
        {
            A_stream <<centerPoint->x << "\t"<<  centerPoint->y;
        }
        else
        {
        	  A_stream << 0 << "\t"<<  0;
        }
       /* if (graphics != NULL)
        {
        	//graphics->drawingAlgorihtm->
        }*/

        return true;
    }
    return false;
}
bool ElementGraphics::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        /*A_stream >> drawing >> selected >>  selected_layer;
        int x,y;
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
