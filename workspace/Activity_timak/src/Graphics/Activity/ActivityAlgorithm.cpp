/*
 * ActivityAlgorithm.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "ActivityAlgorithm.h"

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
#include <sstream>
#include <string>
#include <utility>

#include "../../Core/Activity/Activity.h"
#include "../../DataStructure/Action.h"
#include "../UtilitiesDrawing.h"
#include "ActivityGraphics.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Metamodel/include/ActivityNode.h"

Ogre::FontPtr ActivityAlgorithm::FONT;

ActivityAlgorithm::ActivityAlgorithm() : DrawingAlgorithm()
{
    this->minWidth = 40;
    this->lineHeight = 10;
    this->charWidthMultiplier = 75;
    this->borderHorizontalWidth = 2;
    this->borderVerticalWidth = 2;
    this->cornerSize = 2;
}
ActivityAlgorithm::~ActivityAlgorithm()
{}

void ActivityAlgorithm::draw(const std::string& A_name)
{
	DEF_BEGIN;
    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);
    Metamodel::Action* elemDataCasted;
    ActivityGraphics* elemGraphicsCasted;
    DEFL;
    // Cast control
    if (elem.second->getType() != team4::ActivityNode::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << team4::ActivityNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem.second->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());
        return;
    }
    else
    {
        elemDataCasted = dynamic_cast<Metamodel::Action*>(elem.first->getData());
        elemGraphicsCasted = static_cast<ActivityGraphics*>(elem.first->getGraphics());
        DEFL;
    }

    DEFL;
    this->elemData = elemDataCasted;
    this->elemGraphics = elemGraphicsCasted;

    initFont();
    DEFL;
    // rounded rectangle coordinates precalculation
    int resolution = 44;
    DEFL;
    double finalWidth = getWidth() + 2 * borderVerticalWidth;
    double finalHeight = getHeight() + 2 * borderHorizontalWidth;
    double xl = - finalWidth/2 + cornerSize;
    double xr = finalWidth/2 - cornerSize;
    double yu = finalHeight/2 - cornerSize;
    double yl = - finalHeight/2 + cornerSize;
    double z = 0;
    DEFL;
    Ogre::Real coords[resolution][2];
    Ogre::Degree alpha = (Ogre::Degree) 360 / resolution;
    Ogre::Degree theta = (Ogre::Degree) 0;
    DEFL;
    for (int i = 0; i < 11; ++i)
    { // right upper corner
        theta += alpha;
        coords[i][0] = Ogre::Math::Sin(theta) * cornerSize + xr; // X
        coords[i][1] = Ogre::Math::Cos(theta) * cornerSize + yu; // Y
    }
    for (int i = 11; i < 22; ++i)
    { // right lower corner
        theta += alpha;
        coords[i][0] = Ogre::Math::Sin(theta) * cornerSize + xr; // X
        coords[i][1] = Ogre::Math::Cos(theta) * cornerSize + yl; // Y
    }
    for (int i = 22; i < 33; ++i)
    { // left lower corner
        theta += alpha;
        coords[i][0] = Ogre::Math::Sin(theta) * cornerSize + xl; // X
        coords[i][1] = Ogre::Math::Cos(theta) * cornerSize + yl; // Y
    }
    for (int i = 33; i < 44; ++i)
    { // left upper corner
        theta += alpha;
        coords[i][0] = Ogre::Math::Sin(theta) * cornerSize + xl; // X
        coords[i][1] = Ogre::Math::Cos(theta) * cornerSize + yu; // Y
    }
    // main drawing
    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    manualObject->begin("3D_material_1_material", Ogre::RenderOperation::OT_TRIANGLE_FAN);
    DEFL;
    Ogre::Real writingRectCoords[4][2];
    DEFL;
    for (int i = resolution - 1; i >= 0; --i)
    {
        manualObject->position(coords[i][0], coords[i][1], z);
        if (i == 5)
        { // right upper corner
            writingRectCoords[0][0] = coords[i][0];
            writingRectCoords[0][1] = coords[i][1];
        }
        else if (i == 15)
        { // right lower corner
            writingRectCoords[1][0] = coords[i][0];
            writingRectCoords[1][1] = coords[i][1];
        }
        else if (i == 27)
        { // left lower corner
            writingRectCoords[2][0] = coords[i][0];
            writingRectCoords[2][1] = coords[i][1];
        }
        else if (i == 37)
        { // left upper corner
            writingRectCoords[3][0] = coords[i][0];
            writingRectCoords[3][1] = coords[i][1];
        }
    }
    DEFL;
    manualObject->position(coords[resolution - 1][0], coords[resolution - 1][1], z); // connect last point to first
    DEFL;
    manualObject->end();
    DEFL;
    // writing part
    manualObject->begin(elem.second->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(writingRectCoords[3][0], writingRectCoords[3][1], z);
    manualObject->textureCoord(0, 0);
    manualObject->position(writingRectCoords[0][0], writingRectCoords[0][1], z);
    manualObject->textureCoord(1, 0);
    manualObject->position(writingRectCoords[2][0], writingRectCoords[2][1], z);
    manualObject->textureCoord(0, 1);
    manualObject->position(writingRectCoords[1][0], writingRectCoords[1][1], z);
    manualObject->textureCoord(1, 1);
    manualObject->end();
    DEFL;

    // border drawing
    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    for (int i = resolution - 1; i >= 0; --i)
    {
        manualObject->position(coords[i][0], coords[i][1], z);
    }
    DEFL;
    manualObject->position(coords[resolution - 1][0], coords[resolution - 1][1], z); // connect last point to first
    manualObject->end();


    // attach manual object to node
    Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
    DEFL;
    node->attachObject(manualObject);

    DEFL;
    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem.second->getName() + "_material", "General");
    DEFL;
    elem.first->material = material;
    DEFL;
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem.second->getName() + "_texture");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    DEFL;
    Ogre::MaterialManager::ResourceCreateOrRetrieveResult materialResult = Ogre::MaterialManager::getSingleton().createOrRetrieve("3D_material_1_material", "General");
    Ogre::MaterialPtr materialBase = materialResult.first;
    DEFL;
   /* if (materialResult.second)
    {
        materialBase->getTechnique(0)->getPass(0)->createTextureUnitState("3D_material_1.png");
        materialBase->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
        materialBase->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        materialBase->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    }*/
    DEFL;
    // TEXTURE
    double textureSizeScale = 5;
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
                                   elem.second->getName() + "_texture",
                                   "General",
                                   Ogre::TEX_TYPE_2D,
                                   textureSizeScale * finalWidth,
                                   textureSizeScale * finalHeight,
                                   Ogre::MIP_UNLIMITED,
                                   Ogre::PF_X8R8G8B8,
                                   Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);
    DEFL;
    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_1.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());

    DEFL;
    UtilitiesDrawing::writeToTexture(
        elemDataCasted->getName(),
        texture,
        Ogre::Image::Box(
            textureSizeScale * borderVerticalWidth,
            textureSizeScale * borderHorizontalWidth,
            textureSizeScale * (getWidth() + borderVerticalWidth + cornerSize * 0.5),
            textureSizeScale * (getHeight() + borderHorizontalWidth + cornerSize * 0.5)),
        FONT.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'c',
        true);
    DEFL;
}


void ActivityAlgorithm::select(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);
}
void ActivityAlgorithm::unselected(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
}

double ActivityAlgorithm::getWidth()
{
    double width = 0;
    unsigned int c;
    std::string s;
    // TODO: More precise space width
    double spaceSize = FONT->getGlyphInfo('O').uvRect.width() * charWidthMultiplier * 4;

    s = elemData->getName();
    for(c = 0; c < s.length(); c++)
    {
        if (s[c] == ' ')
            // use '0' size instead of space
            width += spaceSize;
        else
            width += FONT->getGlyphInfo(s[c]).uvRect.width() * charWidthMultiplier;
    }

    //	delete f;

    if (width > minWidth)
    {
        return width;
    }
    else
    {
        return minWidth;
    }
}

double ActivityAlgorithm::getHeight()
{
    return 1.05 * lineHeight;
}

// TODO: temporary version!!
double ActivityAlgorithm::getFullWidth(Element* elem)
{
    this->elemData = dynamic_cast<Metamodel::Action*>(elem->getData());

    return getWidth() + 2 * borderVerticalWidth;
}

// TODO: temporary version!!
double ActivityAlgorithm::getFullHeight(Element* elem)
{
    this->elemData = dynamic_cast<Metamodel::Action*>(elem->getData());

    return getHeight() + 2 * borderHorizontalWidth;
}

void ActivityAlgorithm::initFont()
{
    if (FONT.isNull())
    {
        FONT = Ogre::FontManager::getSingleton().create("Activity_font", "General");
        FONT->setType(Ogre::FT_TRUETYPE);
        FONT->setSource("bluebold.ttf");
        FONT->setTrueTypeSize(40);
        FONT->setTrueTypeResolution(100);
        FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        FONT->load();
    }
}

void ActivityAlgorithm::cleanUp()
{
    FONT.setNull();
}
