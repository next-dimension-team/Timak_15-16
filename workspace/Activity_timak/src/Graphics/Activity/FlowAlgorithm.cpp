/*
 * FlowAlgorithm.cpp
 *
 *  Created on: 17.10.2013
 *      Author: Schade
 */

#include "FlowAlgorithm.h"

#include <OgreLogManager.h>
#include <OgreManualObject.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Element.h"
#include "../../Core/Metamodel/include/ActivityEdge.h"
#include "../../Core/Metamodel/include/FlowFInalNode.h"
#include "../../Core/Utilities.h"
#include "FlowGraphics.h"
#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/Metamodel.h"
#include "../../ApplicationManagement/ApplicationStateManager.h"
#include "../../ApplicationManagement/Mvc/Gui.h"
#include "../UtilitiesDrawing.h"


#include <OgreBlendMode.h>
#include <OgreColourValue.h>
#include <OgreCommon.h>
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreImage.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMath.h>
#include <OgrePass.h>
#include <OgrePixelFormat.h>
#include <OgrePrerequisites.h>
#include <OgreRenderOperation.h>
#include <OgreResourceManager.h>
#include <OgreSceneNode.h>
#include <OgreSharedPtr.h>
#include <OgreTechnique.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>

Ogre::FontPtr FlowAlgorithm::FONT;

FlowAlgorithm::FlowAlgorithm() : DrawingAlgorithm()
{}

FlowAlgorithm::~FlowAlgorithm()
{}

void FlowAlgorithm::draw(const std::string& A_name)
{

    enum Direction {RIGHT_UP, RIGHT_DOWN, LEFT_UP, LEFT_DOWN, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

    Direction direction = UP_LEFT;

    FlowGraphics* elemGraphicsCasted;
    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);
    if (elem.second->getType() != team4::ActivityEdge::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os <<  team4::FlowFinalNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem.second->getType();
        os << "'.";
        Ogre::LogManager::getSingleton().logMessage(os.str());
        return;
    }
    else
    {
        elemGraphicsCasted = static_cast<FlowGraphics*>(elem.first->getGraphics());
    }

    team4::Gui* gui = dynamic_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext());
    bool straight = gui->GetFlowStraight();

    Element* source = Utilities::getConnectorSource(A_name);
    Element* target = Utilities::getConnectorTarget(A_name);

    std::cout << "Layers " << source->getLayer() << ", " << target->getLayer() << ", " << source->getLayer().compare(target->getLayer()) << ", " << straight << std::endl;



    Ogre::Vector3 begin = source->getGraphics()->getConnectorBeginPoint(A_name);
    if(!straight && (source->getLayer().compare(target->getLayer()) == 0))
    {

        Ogre::Vector3 begin = source->getGraphics()->getConnectorBeginPoint(A_name);
        Ogre::Vector2* beg = source->getCenter();

        Ogre::Vector2* end = target->getCenter();

        int xLen = end->x - beg->x;
        int yLen = end->y - beg->y;

        int xStart = beg->x;
        int xEnd = end->x;
        int yStart = beg->y;
        int yEnd = end->y;

        bool free = true;
        std::pair<Element*, team4::MetamodelElement*> element;

        if(xLen <= 0 && yLen > 0)
        {
            for(int x = (xStart - 20); x > xEnd; --x)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(x, yStart));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            for(int y = yStart; y < (yEnd - 20); ++y)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(xEnd, y));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            if(free)
            {
                direction = LEFT_UP;
            }
            else
            {
                direction = UP_LEFT;
            }
        }
        else if(xLen > 0 && yLen >= 0)
        {
            for(int x = (xStart + 20); x < xEnd; ++x)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(x, yStart));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            for(int y = yStart; y < (yEnd - 20); ++y)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(xEnd, y));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            if(free)
            {
                direction = RIGHT_UP;
            }
            else
            {
                direction = UP_RIGHT;
            }
        }
        else if(xLen < 0 && yLen <= 0)
        {
            for(int x = (xStart - 20); x > xEnd; --x)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(x, yStart));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            for(int y = yStart; y > (yEnd + 20); --y)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(xEnd, y));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            if(free)
            {
                direction = LEFT_DOWN;
            }
            else
            {
                direction = DOWN_LEFT;
            }
        }
        else if(xLen >= 0 && yLen < 0)
        {
            for(int x = (xStart + 20); x < xEnd; ++x)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(x, yStart));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            for(int y = yStart; y > (yEnd + 20); --y)
            {
                element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(xEnd, y));
                if(element.first != NULL)
                {
                    free = false;
                }
            }

            if(free)
            {
                direction = RIGHT_DOWN;
            }
            else
            {
                direction = DOWN_RIGHT;
            }
        }

        Ogre::Vector3 beginOrigin = source->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
        Ogre::Vector3 beginLocal = Ogre::Vector3(begin.distance(beginOrigin), 0, 0);

        Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
        manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
        if(direction == RIGHT_UP)
        {
            manualObject->position(beginLocal);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 3, beginLocal.y + yLen - 6, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 3, beginLocal.y + yLen - 6, 0);
        }
        else if(direction == LEFT_UP)
        {
            manualObject->position(beginLocal);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 3, beginLocal.y + yLen - 6, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 3, beginLocal.y + yLen - 6, 0);
        }
        else if(direction == RIGHT_DOWN)
        {
            manualObject->position(beginLocal);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 3, beginLocal.y + yLen + 6, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 3, beginLocal.y + yLen + 6, 0);
        }
        else if(direction == LEFT_DOWN)
        {
            manualObject->position(beginLocal);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, 0, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 3, beginLocal.y + yLen + 6, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 3, beginLocal.y + yLen + 6, 0);
        }
        else if(direction == UP_RIGHT)
        {
            manualObject->position(0, beginLocal.x, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 6, beginLocal.y + yLen + 3, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 6, beginLocal.y + yLen -3, 0);
        }
        else if(direction == DOWN_RIGHT)
        {
            manualObject->position(0, beginLocal.x, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 6, beginLocal.y + yLen + 3, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen - 6, beginLocal.y + yLen -3, 0);
        }
        else if(direction == UP_LEFT)
        {
            manualObject->position(0, beginLocal.x, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 6, beginLocal.y + yLen + 3, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 6, beginLocal.y + yLen -3, 0);
        }
        else if(direction == DOWN_LEFT)
        {
            manualObject->position(0, beginLocal.x, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(0, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 6, beginLocal.y + yLen + 3, 0);
            manualObject->position(beginLocal.x + xLen, beginLocal.y + yLen, 0);
            manualObject->position(beginLocal.x + xLen + 6, beginLocal.y + yLen -3, 0);
        }
        manualObject->end();
        elemGraphicsCasted->getSceneNode()->attachObject(manualObject);
    }
    else
    {
        Ogre::Vector3 vecBegin = source->getGraphics()->getConnectorBeginPoint(A_name);
        Ogre::Vector3 vecEnd = target->getGraphics()->getConnectorEndPoint(A_name);
        double len = vecBegin.distance(vecEnd);
        Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
        manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
        Ogre::Vector3 beginOrigin = source->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
        Ogre::Vector3 vecBeginLocal = Ogre::Vector3(vecBegin.distance(beginOrigin), 0, 0);
        manualObject->position(vecBeginLocal);
        manualObject->position(vecBeginLocal.x + len, 0, 0);
        manualObject->position(vecBeginLocal.x + len, 0, 0);
        manualObject->position(vecBeginLocal.x + len - 6, - 3, 0);
        manualObject->position(vecBeginLocal.x + len, 0, 0);
        manualObject->position(vecBeginLocal.x + len - 6, 3, 0);
        manualObject->end();
        Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
        node->attachObject(manualObject);
        Ogre::Vector3 vecDiff = vecEnd - vecBegin;

        if(vecDiff.z < 0)
        {
            node->yaw((new Ogre:: Vector3(len, 0, 0))->angleBetween(*(new Ogre::Vector3(vecDiff.x, 0, vecDiff.z))), Ogre::Node::TS_LOCAL);
        }
        else if(vecDiff.z > 0 || vecDiff.x != 0)
        {
            node->yaw(-(new Ogre:: Vector3(len, 0, 0))->angleBetween(*(new Ogre::Vector3(vecDiff.x, 0, vecDiff.z))), Ogre::Node::TS_LOCAL);
        }

        if(vecDiff.y < 0)
        {
            node->roll(-(new Ogre:: Vector3(len, 0, 0))->angleBetween(*(new Ogre::Vector3(sqrt(pow(vecDiff.x, 2) + pow(vecDiff.z, 2)), vecDiff.y, 0))), Ogre::Node::TS_LOCAL);
        }
        else if(vecDiff.y > 0)
        {
            node->roll((new Ogre:: Vector3(len, 0, 0))->angleBetween(*(new Ogre::Vector3(sqrt(pow(vecDiff.x, 2) + pow(vecDiff.z, 2)), vecDiff.y, 0))), Ogre::Node::TS_LOCAL);
        }
    }

    std::string text = static_cast<team4::ActivityEdge*>(elem.second)->text;
    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem.second->getName() + "_material", "General");
    DEFL;
    elem.first->material = material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem.second->getName() + "_texture");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);

    Ogre::MaterialManager::ResourceCreateOrRetrieveResult materialResult = Ogre::MaterialManager::getSingleton().createOrRetrieve("3D_material_1_material", "General");
    Ogre::MaterialPtr materialBase = materialResult.first;
    DEFL;
    if (materialResult.second)
    {
        materialBase->getTechnique(0)->getPass(0)->createTextureUnitState("3D_material_1.png");
        materialBase->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
        materialBase->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    }


    Ogre::Vector3 beginOrigin = source->getGraphics()->getSceneNode()->convertLocalToWorldPosition(Ogre::Vector3::ZERO);
    Ogre::Vector3 beginLocal = Ogre::Vector3(begin.distance(beginOrigin), 0, 0);
    beginLocal.x += 5;
    beginLocal.y += 5;
    initFont();
    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    manualObject->begin(elem.second->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(beginLocal.x, beginLocal.y+7, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(beginLocal.x+text.length()*5, beginLocal.y+7, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(beginLocal.x, beginLocal.y, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(beginLocal.x+text.length()*5, beginLocal.y, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();


    // TEXTURE

    double textureSizeScale = 5;
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
                                   elem.second->getName() + "_texture",
                                   "General",
                                   Ogre::TEX_TYPE_2D,
                                   text.length()*7*textureSizeScale*1.05,
                                   20*textureSizeScale/1.4,
                                   Ogre::MIP_UNLIMITED,
                                   Ogre::PF_X8R8G8B8,
                                   Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_white.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());


    std::string str = static_cast<team4::ActivityEdge*>(elem.second)->text;
    UtilitiesDrawing::writeToTexture(
        text.c_str(),
        texture,
        Ogre::Image::Box(
            0,
            0,
            text.length()*4*textureSizeScale*3.5,
            60*textureSizeScale*3.5),
        FONT.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'c',
        true);
}

void FlowAlgorithm::select(Element* elem)
{}

void FlowAlgorithm::unselected(Element* elem)
{}

void FlowAlgorithm::initFont()
{
    if (FONT.isNull())
    {
        FONT = Ogre::FontManager::getSingleton().create("Flow_font", "General");
        FONT->setType(Ogre::FT_TRUETYPE);
        FONT->setSource("bluebold.ttf");
        FONT->setTrueTypeSize(40);
        FONT->setTrueTypeResolution(100);
        FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        FONT->load();
    }
}

void FlowAlgorithm::cleanUp()
{
    FONT.setNull();
}
