/*
 * ClassAlgorithm.cpp
 *
 *  Created on: 24.6.2013
 *      Author: Schade
 */

#include "ClassAlgorithm.h"

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
#include <OgrePass.h>
#include <OgrePixelFormat.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreSharedPtr.h>
#include <OgreTechnique.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../Core/Class.h"
#include "../DataStructure/Class.h"
#include "../DataStructure/Operation.h"
#include "../DataStructure/Property.h"
#include "ClassGraphics.h"
#include "UtilitiesDrawing.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"



Ogre::FontPtr ClassAlgorithm::FONT_HEADER;
Ogre::FontPtr ClassAlgorithm::FONT_ATTRIBUTE;

ClassAlgorithm::ClassAlgorithm() : DrawingAlgorithm()
{
    this->minWidth = 20;
    this->lineHeight = 3.8;
    this->charWidthMultiplier = 52;
    this->borderHorizontalWidth = 2;
    this->borderVerticalWidth = 4;
}
ClassAlgorithm::~ClassAlgorithm()
{}

void ClassAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Class* elemCasted;
    Metamodel::Class* elemDataCasted;

    // Cast control
    if (elem->getType() != Class::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Class::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Class*>(elem);
        elemDataCasted = dynamic_cast<Metamodel::Class*>(elem->getData());
    }

    this->elem = elemCasted;
    this->elemData = elemDataCasted;

    initFonts();

    double finalWidth = getWidth() + 2 * borderVerticalWidth;
    double finalHeight = getHeight() + 3 * borderHorizontalWidth;
    double xl = - finalWidth/2;
    double xr = finalWidth/2;
    double yu = finalHeight/2;
    double yl = - finalHeight/2;
    double z = 0;
    double upperSeparator = yu - getHeaderHeight() - 1.25 * borderHorizontalWidth;
    double lowerSeparator = upperSeparator - getAttributesHeight() - borderHorizontalWidth;

    Ogre::ManualObject* manualObject = elem->getGraphics()->getManualObject();
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(xl, yu, z);
    manualObject->textureCoord(0, 0);
    manualObject->position(xr, yu, z);
    manualObject->textureCoord(1, 0);
    manualObject->position(xl, yl, z);
    manualObject->textureCoord(0, 1);
    manualObject->position(xr, yl, z);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
    manualObject->position(xl, upperSeparator, z);
    manualObject->position(xr, upperSeparator, z);
    manualObject->position(xl, lowerSeparator, z);
    manualObject->position(xr, lowerSeparator, z);
    manualObject->position(xl, yu, z);
    manualObject->position(xl, yl, z);
    manualObject->position(xl, yl, z);
    manualObject->position(xr, yl, z);
    manualObject->position(xr, yl, z);
    manualObject->position(xr, yu, z);
    manualObject->position(xr, yu, z);
    manualObject->position(xl, yu, z);
    manualObject->end();

    Ogre::SceneNode* node = elem->getGraphics()->getSceneNode();
    node->attachObject(manualObject);


    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem->getName() + "_material", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "_texture");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);

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

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_1.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());


    UtilitiesDrawing::writeToTexture(
        elemDataCasted->getName(),
        texture,
        Ogre::Image::Box(
            textureSizeScale * borderVerticalWidth,
            textureSizeScale * borderHorizontalWidth,
            textureSizeScale * (getWidth() + borderVerticalWidth),
            textureSizeScale * (getHeaderHeight() + borderHorizontalWidth)),
        FONT_HEADER.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'c',
        true);

    UtilitiesDrawing::writeToTexture(
        elemCasted->getAttributesText(),
        texture,
        Ogre::Image::Box(
            textureSizeScale * borderVerticalWidth,
            textureSizeScale * (getHeaderHeight() + 2 * borderHorizontalWidth),
            textureSizeScale * (getWidth() + borderVerticalWidth),
            textureSizeScale * (getHeaderHeight() + getAttributesHeight() + 2 * borderHorizontalWidth)),
        FONT_ATTRIBUTE.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'l',
        true);

    UtilitiesDrawing::writeToTexture(
        elemCasted->getMethodsText(),
        texture,
        Ogre::Image::Box(
            textureSizeScale * borderVerticalWidth,
            textureSizeScale * (getHeaderHeight() + getAttributesHeight() + 3 * borderHorizontalWidth),
            textureSizeScale * (getWidth() + borderVerticalWidth),
            textureSizeScale * (getHeaderHeight() + getAttributesHeight() + getMethodsHeight() + 3 * borderHorizontalWidth)),
        FONT_ATTRIBUTE.getPointer(),
        Ogre::ColourValue(0.0,0.0,0.0,1.0),
        'l',
        true);
}

double ClassAlgorithm::getWidth()
{
    double width = 0;
    unsigned int c;
    std::string s;
    // TODO: More precise space width
    initFonts();
    double spaceSize = FONT_HEADER->getGlyphInfo('O').uvRect.width() * charWidthMultiplier * 1.2;

    s = elemData->getName();
    for(c = 0; c < s.length(); c++)
    {
        if (s[c] == ' ')
            // use '0' size instead of space
            width += spaceSize;
        else
            width += FONT_HEADER->getGlyphInfo(s[c]).uvRect.width() * charWidthMultiplier * 2.5;
    }


    double widthTmp;
    unsigned int i;
    // TODO: More precise space width
    spaceSize = FONT_ATTRIBUTE->getGlyphInfo('O').uvRect.width() * charWidthMultiplier * 1.2;

    for(i=0; i < elemData->getAttributes().size(); i++)
    {
        s = static_cast<Metamodel::Property*>(elemData->getAttributes()[i])->getName();

        widthTmp = 0;
        for(c = 0; c < s.length(); c++)
        {
            if (s[c] == ' ')
                // use '0' size instead of space
                widthTmp += spaceSize;
            else
                widthTmp += FONT_ATTRIBUTE->getGlyphInfo(s[c]).uvRect.width() * charWidthMultiplier;
        }

        if (widthTmp > width)
            width = widthTmp;
    }

    for(i=0; i < elemData->getOperations().size(); i++)
    {
        s = static_cast<Metamodel::Operation*>(elemData->getOperations()[i])->getName();

        widthTmp = 0;
        for(c = 0; c < s.length(); c++)
        {
            if (s[c] == ' ')
                // use '0' size instead of space
                widthTmp += spaceSize;
            else
                widthTmp += FONT_ATTRIBUTE->getGlyphInfo(s[c]).uvRect.width() * charWidthMultiplier;
        }

        if (widthTmp > width)
            width = widthTmp;
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

double ClassAlgorithm::getHeight()
{
    double height = getAttributesHeight() + getMethodsHeight() + getHeaderHeight();
    return height;
}

double ClassAlgorithm::getAttributesHeight()
{
    int linesNo = 0;
    std::vector<Metamodel::Property*> v = elemData->getAttributes();
    for (std::vector<Metamodel::Property*>::iterator i = v.begin(); i != v.end(); i++)
    {
        if (!(*i)->getName().empty())
            linesNo++;
    }
    return linesNo * lineHeight;
}

double ClassAlgorithm::getMethodsHeight()
{
    double height = elemData->getOperations().size() * lineHeight;
    return height;
}

double ClassAlgorithm::getHeaderHeight()
{
    double height = 1.1 * lineHeight;
    return height;
}

// TODO: temporary version!!
double ClassAlgorithm::getFullWidth(Element* elem)
{
    this->elemData = dynamic_cast<Metamodel::Class*>(elem->getData());
    this->elemGraphics = static_cast<ClassGraphics*>(elem->getGraphics());

    return getWidth() + 2 * borderVerticalWidth;
}

// TODO: temporary version!!
double ClassAlgorithm::getFullHeight(Element* elem)
{
    this->elemData = dynamic_cast<Metamodel::Class*>(elem->getData());
    this->elemGraphics = static_cast<ClassGraphics*>(elem->getGraphics());

    return getHeight() + 3 * borderHorizontalWidth;
}

void ClassAlgorithm::initFonts()
{
    if (FONT_HEADER.isNull())
    {
        FONT_HEADER = Ogre::FontManager::getSingleton().create("Class_fontHeader", "General");

        FONT_HEADER->setType(Ogre::FT_TRUETYPE);
        FONT_HEADER->setSource("bluebold.ttf");
        FONT_HEADER->setTrueTypeSize(16);
        FONT_HEADER->setTrueTypeResolution(96);
        FONT_HEADER->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        FONT_HEADER->load();
    }

    if (FONT_ATTRIBUTE.isNull())
    {
        FONT_ATTRIBUTE = Ogre::FontManager::getSingleton().create("Class_fontAttribute", "General");

        FONT_ATTRIBUTE->setType(Ogre::FT_TRUETYPE);
        FONT_ATTRIBUTE->setSource("times.ttf");
        FONT_ATTRIBUTE->setTrueTypeSize(12);
        FONT_ATTRIBUTE->setTrueTypeResolution(96);
        FONT_ATTRIBUTE->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        FONT_ATTRIBUTE->load();
    }
}

void ClassAlgorithm::cleanUp()
{
    FONT_HEADER.setNull();
    FONT_ATTRIBUTE.setNull();
}
