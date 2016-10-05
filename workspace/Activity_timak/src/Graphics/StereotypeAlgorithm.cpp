/*
 * StereotypeAlgorithm.cpp
 *
 *  Created on: 1.7.2013
 *      Author: Schade
 */

#include "StereotypeAlgorithm.h"

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
#include <OgrePass.h>
#include <OgrePixelFormat.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreSharedPtr.h>
#include <OgreTechnique.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <OgreVector3.h>
#include <sstream>
#include <string>
#include <utility>

#include "../Core/Stereotype.h"
#include "../DataStructure/Association.h"
#include "StereotypeGraphics.h"
#include "UtilitiesDrawing.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"

Ogre::FontPtr StereotypeAlgorithm::FONT;

StereotypeAlgorithm::StereotypeAlgorithm() : DrawingAlgorithm()
{
    this->minWidth = 10;
    this->lineHeight = 3.8;
    this->charWidthMultiplier = 52;
    this->borderHorizontalWidth = 1;
    this->borderVerticalWidth = 0.5;
    this->borderTriangleWidth = 6;
}
StereotypeAlgorithm::~StereotypeAlgorithm()
{}

void StereotypeAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Metamodel::Association* elemDataCasted;
    StereotypeGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Stereotype::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Stereotype::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemDataCasted = dynamic_cast<Metamodel::Association*>(elem->getData());
        elemGraphicsCasted = static_cast<StereotypeGraphics*>(elem->getGraphics());
    }

    this->elemData = elemDataCasted;
    this->elemGraphics = elemGraphicsCasted;

    initFont();

    if (elemDataCasted->getStereotype().compare("") == 0)
    {
        // TODO: move to different place
        return;
    }

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    double finalWidth = getWidth() + 2 * borderVerticalWidth;
    double finalHeight = getHeight() + 2 * borderHorizontalWidth;
    Ogre::Vector3 differenceVector = elemGraphicsCasted->getDifferenceVector();

    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

    // Lower Left Point
    manualObject->position(-finalWidth, 0, 0);
    if (differenceVector.z < 0 && differenceVector.x == 0)
        manualObject->textureCoord(1, 1);
    else if (differenceVector.x < 0)
        manualObject->textureCoord(1, 1);
    else
        manualObject->textureCoord(0, 1);

    // Upper Left Point
    manualObject->position(-finalWidth, finalHeight, 0);
    if (differenceVector.z < 0 && differenceVector.x == 0)
        manualObject->textureCoord(1, 0);
    else if (differenceVector.x < 0)
        manualObject->textureCoord(1, 0);
    else
        manualObject->textureCoord(0, 0);

    // Lower Right Point
    manualObject->position(finalWidth, 0, 0);
    if (differenceVector.z < 0 && differenceVector.x == 0)
        manualObject->textureCoord(0, 1);
    else if (differenceVector.x < 0)
        manualObject->textureCoord(0, 1);
    else
        manualObject->textureCoord(1, 1);

    // Upper Right Point
    manualObject->position(finalWidth, finalHeight, 0);
    if (differenceVector.z < 0 && differenceVector.x == 0)
        manualObject->textureCoord(0, 0);
    else if (differenceVector.x < 0)
        manualObject->textureCoord(0, 0);
    else
        manualObject->textureCoord(1, 0);


    manualObject->end();

    // Left Triangle
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_LIST);
    manualObject->position(-finalWidth, 0, 0);
    manualObject->position(-finalWidth, finalHeight, 0);
    manualObject->position(-borderTriangleWidth - finalWidth, 0, 0);
    manualObject->end();

    // Right Triangle
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_LIST);
    manualObject->position(finalWidth, 0, 0);
    manualObject->position(finalWidth, finalHeight, 0);
    manualObject->position(borderTriangleWidth + finalWidth, 0, 0);
    manualObject->end();

    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem->getName() + "_material", "General");
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "_texture");

    Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
    node->attachObject(manualObject);

    // TEXTURE
    double textureSizeScale = 5;
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
                                   elem->getName() + "_texture",
                                   "General",
                                   Ogre::TEX_TYPE_2D,
                                   textureSizeScale * finalWidth,
                                   textureSizeScale * finalHeight,
                                   Ogre::MIP_UNLIMITED,
                                   Ogre::PF_X8R8G8B8,
                                   Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_UML_Layer.png", "General").getPointer();

    //Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());

    UtilitiesDrawing::writeToTexture(
        elemDataCasted->getStereotype(),
        texture,
        Ogre::Image::Box(
            textureSizeScale * borderVerticalWidth,
            textureSizeScale * borderHorizontalWidth,
            textureSizeScale * (getWidth() + borderVerticalWidth),
            textureSizeScale * (getHeight() + borderHorizontalWidth)),
        FONT.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'c',
        true);
}

double StereotypeAlgorithm::getWidth()
{
    double width = 0;
    unsigned int c;
    std::string s;
    // TODO: More precise space width
    double spaceSize = FONT->getGlyphInfo('O').uvRect.width() * charWidthMultiplier * 1.4;

    s = elemData->getStereotype();
    for(c = 0; c < s.length(); c++)
    {
        if (s[c] == ' ')
            // use '0' size instead of space
            width += spaceSize;
        else
            width += FONT->getGlyphInfo(s[c]).uvRect.width() * charWidthMultiplier;
    }

    if (width > minWidth)
    {
        return width;
    }
    else
    {
        return minWidth;
    }
}

double StereotypeAlgorithm::getHeight()
{
    return lineHeight;
}

void StereotypeAlgorithm::initFont()
{
    if (FONT.isNull())
    {
        FONT = Ogre::FontManager::getSingleton().create("Stereotype_font", "General");

        FONT->setType(Ogre::FT_TRUETYPE);
        FONT->setSource("times.ttf");
        FONT->setTrueTypeSize(12);
        FONT->setTrueTypeResolution(96);
        FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        FONT->load();
    }
}

void StereotypeAlgorithm::cleanUp()
{
    FONT.setNull();
}
