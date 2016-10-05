/*
 * FragmentAlgorithm.cpp
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */


#include "FragmentAlgorithm.h"

#include <OgreColourValue.h>
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
#include <sstream>
#include <string>
#include <utility>

#include "../../Core/Activity/Fragment.h"
#include "../../DataStructure/ActivityFragment.h"
#include "../UtilitiesDrawing.h"
#include "FragmentGraphics.h"


#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"

#include "../../Core/Metamodel/include/ConditionNode.h"
#include "../../Core/Metamodel/include/LoopNode.h"
#include "../../Core/Metamodel/include/SequenceNode.h"


Ogre::FontPtr FragmentAlgorithm::BOOKMARK_FONT;
Ogre::FontPtr FragmentAlgorithm::TYPE_FONT;
Ogre::FontPtr FragmentAlgorithm::CONDITION_FONT;

FragmentAlgorithm::FragmentAlgorithm() : DrawingAlgorithm()
{
    this->headerLineHeight = 10;
    this->bookmarkFieldWidth = this->headerLineHeight;
    this->typeFieldWidth = 5 * this->headerLineHeight;
    this->textureSizeScale = 5;
}

FragmentAlgorithm::~FragmentAlgorithm()
{}

void FragmentAlgorithm::drawAlt(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Fragment* elemCasted;
    Metamodel::ActivityFragment* elemDataCasted;
    FragmentGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Fragment::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Fragment::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Fragment*>(elem);
        elemDataCasted = dynamic_cast<Metamodel::ActivityFragment*>(elem->getData());
        elemGraphicsCasted = static_cast<FragmentGraphics*>(elem->getGraphics());
    }

    initFonts();

    float count = static_cast<team4::ConditionNode*>(element.second)->cluase.size();
    initTextures(elemCasted,count);
    initMaterials(elemCasted,elem,count);

    Ogre::TexturePtr texture;

    Ogre::ColourValue blackColour = Ogre::ColourValue(0.0,0.0,0.0,1.0);
    Ogre::ColourValue blueColour = Ogre::ColourValue(0.0,0.0,1.0,1.0);

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    float width = elemGraphicsCasted->getWidth();
    float heightOfClause = elemGraphicsCasted->getHeight()/2;
    float height = count*heightOfClause+10;
    float pos = 0;
    count = 0;

    for(auto i:static_cast<team4::ConditionNode*>(element.second)->
            cluase)
    {
        pos += heightOfClause;

        std::ostringstream strCount;
        strCount << count;
        /*manualObject->begin("Fragment_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
        manualObject->position(-width / 2, height / 2 - pos+25, 0);
        manualObject->textureCoord(0, 0);
        manualObject->position(-width / 2 + 5, height / 2 - pos, 0);
        manualObject->textureCoord(0, 1);
        manualObject->position(width / 2 - 5,  height / 2 - pos+25, 0);
        manualObject->textureCoord(1, 0);
        manualObject->position(width / 2 - 5, height / 2 - pos, 0);
        manualObject->textureCoord(1, 1);
        manualObject->end();*/

        manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
        manualObject->position(-width / 2 , height / 2 - pos, 0);
        manualObject->position(-width / 2, height / 2-pos+heightOfClause, 0);
        manualObject->position(width / 2, height / 2- pos+heightOfClause, 0);
        manualObject->position(width / 2, height / 2- pos, 0);
        manualObject->position(-width / 2, height / 2-pos, 0);
        manualObject->end();

        float clause_width = -width / 2;
        float clause_height = height / 2 - pos+heightOfClause;
        manualObject->begin(elem->getName() + "Fragment_material"+strCount.str(), Ogre::RenderOperation::OT_TRIANGLE_STRIP);
        manualObject->position(clause_width+1, clause_height-1, 0);
        manualObject->textureCoord(0, 0);
        manualObject->position(clause_width+1, clause_height-6, 0);
        manualObject->textureCoord(0, 1);
        manualObject->position(clause_width+34, clause_height-1, 0);
        manualObject->textureCoord(1, 0);
        manualObject->position(clause_width+34, clause_height-6, 0);
        manualObject->textureCoord(1, 1);
        manualObject->end();

        manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
        manualObject->position(clause_width, clause_height, 0);
        manualObject->position(clause_width, clause_height -7, 0);
        manualObject->position(clause_width+35, clause_height -7, 0);
        manualObject->position(clause_width+40, clause_height -4, 0);
        manualObject->position(clause_width+40, clause_height, 0);
        manualObject->position(clause_width, clause_height, 0);
        manualObject->end();

        texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Clause_texture"+strCount.str(), "General");

        std::string str = i->condiotion;
        std::cout<<str<<std::endl;
        UtilitiesDrawing::writeToTexture(
            str,
            texture,
            Ogre::Image::Box(
                0,
                this->textureSizeScale * 1,
                this->textureSizeScale * this->bookmarkFieldWidth*10,
                this->textureSizeScale * this->headerLineHeight),
            BOOKMARK_FONT.getPointer(),
            blackColour,
            'l',
            true);
        count++;
    }
    widthE = width  / 2;
    heightE = height / 2;

    manualObject->begin("Fragment_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-width / 2, height /2+ this->headerLineHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(-width / 2, -height/2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(width / 2, height /2+ this->headerLineHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(width / 2, -height/2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(-width / 2, height/2+ this->headerLineHeight, 0);
    manualObject->position(-width / 2, -height/2, 0);
    manualObject->position(width / 2, -height/2, 0);
    manualObject->position(width / 2, height/2+ this->headerLineHeight, 0);
    manualObject->position(-width / 2, height/2+ this->headerLineHeight, 0);
    manualObject->end();

    float bookmarkWidth = width / 2 - this->bookmarkFieldWidth;
    float newHeight = height/2 + this->headerLineHeight;

    // ------------------------- BOOKMARK BUTTON -------------------------
    /*Ogre::ManualObject* bookmarkManualObject = elemGraphicsCasted->getBookmarkManualObject();
    bookmarkManualObject->begin(elem->getName() + "Bookmark_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->textureCoord(0, 0);
    bookmarkManualObject->position(bookmarkWidth, height/2, 0);
    bookmarkManualObject->textureCoord(0, 1);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->textureCoord(1, 0);
    bookmarkManualObject->position(width / 2, height/2, 0);
    bookmarkManualObject->textureCoord(1, 1);
    bookmarkManualObject->end();

    bookmarkManualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, height/2, 0);
    bookmarkManualObject->position(width / 2, height/2, 0);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->end();*/



    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Bookmark_texture", "General");

    std::ostringstream fragmentsCount;
    fragmentsCount << elemCasted->getCollectionFragmentsCount();

    UtilitiesDrawing::writeToTexture(
        fragmentsCount.str(),
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 1,
            this->textureSizeScale * this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        BOOKMARK_FONT.getPointer(),
        blackColour,
        'c',
        true);

    float typeWidth = 20;

    // ------------------------- TYPE FIELD -------------------------
    /*manualObject->begin(elem->getName() + "Type_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(typeWidth, height/2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(bookmarkWidth, height/2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->position(typeWidth, height/2, 0);
    manualObject->position(bookmarkWidth, height/2, 0);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Type_texture", "General");

    UtilitiesDrawing::writeToTexture(
        "Alt",
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 3,
            this->textureSizeScale * this->typeFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        TYPE_FONT.getPointer(),
        blueColour,
        'c',
        true);*/

    // ------------------------- CONDITION FIELD -------------------------
    float conditionWidth = - width / 2;

    manualObject->begin(elem->getName() + "Condition_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(conditionWidth, height/2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(typeWidth, height/2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->position(conditionWidth, height/2, 0);
    manualObject->position(conditionWidth+ typeWidth-5, height/2, 0);
    manualObject->position(conditionWidth+ typeWidth, height/2+5, 0);
    manualObject->position(conditionWidth+ typeWidth, newHeight, 0);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->end();


    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Condition_texture", "General");

    UtilitiesDrawing::writeToTexture(
        "Alt",
        texture,
        Ogre::Image::Box(
            this->textureSizeScale * 10,
            this->textureSizeScale * 2,
            this->textureSizeScale * width - this->typeFieldWidth - this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        CONDITION_FONT.getPointer(),
        blackColour,
        'l',
        true);

    elemGraphicsCasted->getSceneNode()->attachObject( manualObject );
    //elemGraphicsCasted->getSceneNode()->attachObject( bookmarkManualObject );




}



void FragmentAlgorithm::drawLoop(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Fragment* elemCasted;
    Metamodel::ActivityFragment* elemDataCasted;
    FragmentGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Fragment::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Fragment::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Fragment*>(elem);
        elemDataCasted = dynamic_cast<Metamodel::ActivityFragment*>(elem->getData());
        elemGraphicsCasted = static_cast<FragmentGraphics*>(elem->getGraphics());
    }

    initFonts();
    initTextures(elemCasted,1);
    initMaterials(elemCasted,elem,1);

    Ogre::TexturePtr texture;

    Ogre::ColourValue blackColour = Ogre::ColourValue(0.0,0.0,0.0,1.0);

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    float width = elemGraphicsCasted->getWidth();
    float height = elemGraphicsCasted->getHeight();
    float height2 = elemGraphicsCasted->getHeight()-10;
    /*manualObject->begin("Fragment_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-width2 / 2, height2 / 2, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(-width2 / 2, -height2 / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(width2 / 2, height2 / 2, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(width2 / 2, -height2 / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();*/

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(-width / 2, height2 / 2, 0);
    manualObject->position(-width / 2, -height2 / 2, 0);
    manualObject->position(width / 2, -height2 / 2, 0);
    manualObject->position(width / 2, height2 / 2, 0);
    manualObject->position(-width / 2, height2 / 2, 0);
    manualObject->end();

    float clause_width = -width / 2;
    float clause_height = height2 / 2;
    manualObject->begin(elem->getName() + "Fragment_material0", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(clause_width+1, clause_height-1, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(clause_width+1, clause_height-6, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(clause_width+35, clause_height-1, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(clause_width+35, clause_height-6, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(clause_width, clause_height, 0);
    manualObject->position(clause_width, clause_height -7, 0);
    manualObject->position(clause_width+35, clause_height -7, 0);
    manualObject->position(clause_width+40, clause_height -4, 0);
    manualObject->position(clause_width+40, clause_height, 0);
    manualObject->position(clause_width, clause_height, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Clause_texture0", "General");

    std::string str = static_cast<team4::LoopNode*>(element.second)->cond;
    UtilitiesDrawing::writeToTexture(
        str,
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 1,
            this->textureSizeScale * this->bookmarkFieldWidth*20,
            this->textureSizeScale * this->headerLineHeight),
        BOOKMARK_FONT.getPointer(),
        blackColour,
        'l',
        true);
    widthE = width  / 2;
    heightE = height / 2;
    manualObject->begin("Fragment_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-width / 2, height / 2+ this->headerLineHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(-width / 2, -height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(width / 2, height / 2+this->headerLineHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(width / 2, -height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(-width / 2, height / 2+this->headerLineHeight, 0);
    manualObject->position(-width / 2, -height / 2, 0);
    manualObject->position(width / 2, -height / 2, 0);
    manualObject->position(width / 2, height / 2+this->headerLineHeight, 0);
    manualObject->position(-width / 2, height / 2+this->headerLineHeight, 0);
    manualObject->end();

    float bookmarkWidth = width / 2 - this->bookmarkFieldWidth;
    float newHeight = height / 2 + this->headerLineHeight;

    // ------------------------- BOOKMARK BUTTON -------------------------
    /*Ogre::ManualObject* bookmarkManualObject = elemGraphicsCasted->getBookmarkManualObject();
    bookmarkManualObject->begin(elem->getName() + "Bookmark_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->textureCoord(0, 0);
    bookmarkManualObject->position(bookmarkWidth, height / 2, 0);
    bookmarkManualObject->textureCoord(0, 1);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->textureCoord(1, 0);
    bookmarkManualObject->position(width / 2, height / 2, 0);
    bookmarkManualObject->textureCoord(1, 1);
    bookmarkManualObject->end();

    bookmarkManualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, height / 2, 0);
    bookmarkManualObject->position(width / 2, height / 2, 0);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->end();



    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Bookmark_texture", "General");

    std::ostringstream fragmentsCount;
    fragmentsCount << elemCasted->getCollectionFragmentsCount();

    UtilitiesDrawing::writeToTexture(
        fragmentsCount.str(),
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 1,
            this->textureSizeScale * this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        BOOKMARK_FONT.getPointer(),
        blackColour,
        'c',
        true);*/

    float typeWidth = bookmarkWidth - this->typeFieldWidth;

    // ------------------------- TYPE FIELD -------------------------
    /*manualObject->begin(elem->getName() + "Type_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(bookmarkWidth, height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->position(bookmarkWidth, height / 2, 0);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Type_texture", "General");

    UtilitiesDrawing::writeToTexture(
        "Loop",
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 3,
            this->textureSizeScale * this->typeFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        TYPE_FONT.getPointer(),
        blueColour,
        'c',
        true);*/

    // ------------------------- CONDITION FIELD -------------------------
    float conditionWidth = - width / 2;

    manualObject->begin(elem->getName() + "Condition_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(conditionWidth, height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->position(conditionWidth, height / 2, 0);
    manualObject->position(typeWidth-5, height / 2, 0);
    manualObject->position(typeWidth, newHeight-5, 0);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Condition_texture", "General");
    std::string str2 = "Loop ["+static_cast<team4::LoopNode*>(element.second)->init+"]";
    UtilitiesDrawing::writeToTexture(
        str2,
        texture,
        Ogre::Image::Box(
            this->textureSizeScale * 10,
            this->textureSizeScale * 2,
            this->textureSizeScale * width - this->typeFieldWidth - this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        CONDITION_FONT.getPointer(),
        blackColour,
        'l',
        true);

    elemGraphicsCasted->getSceneNode()->attachObject( manualObject );
    //elemGraphicsCasted->getSceneNode()->attachObject( bookmarkManualObject );
}


void FragmentAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    if (element.second->getType() == team4::ConditionNode::ELEMENT_TYPE)
    {
        drawAlt(A_name);
        return;
    }
    else if (element.second->getType() == team4::StructuredActivityNode::ELEMENT_TYPE)
    {
        drawSeq(A_name);
        return;
    }
    else if (element.second->getType() == team4::LoopNode::ELEMENT_TYPE)
    {
        drawLoop(A_name);
        return;
    }
}

void FragmentAlgorithm::drawSeq(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Fragment* elemCasted;
    Metamodel::ActivityFragment* elemDataCasted;
    FragmentGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Fragment::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Fragment::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Fragment*>(elem);
        elemDataCasted = dynamic_cast<Metamodel::ActivityFragment*>(elem->getData());
        elemGraphicsCasted = static_cast<FragmentGraphics*>(elem->getGraphics());
    }

    initFonts();
    initTextures(elemCasted,0);
    initMaterials(elemCasted,elem,0);

    Ogre::TexturePtr texture;

    Ogre::ColourValue blackColour = Ogre::ColourValue(0.0,0.0,0.0,1.0);
    Ogre::ColourValue blueColour = Ogre::ColourValue(0.0,0.0,1.0,1.0);

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    float width = elemGraphicsCasted->getWidth();
    float height = elemGraphicsCasted->getHeight();

    widthE = width  / 2;
    heightE = height / 2;
    manualObject->begin("Fragment_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-width / 2, height / 2 + this->headerLineHeight , 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(-width / 2, -height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(width / 2, height / 2 + this->headerLineHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(width / 2, -height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(-width / 2, height / 2 + this->headerLineHeight, 0);
    manualObject->position(-width / 2, -height / 2, 0);
    manualObject->position(width / 2, -height / 2, 0);
    manualObject->position(width / 2, height / 2 + this->headerLineHeight, 0);
    manualObject->position(-width / 2, height / 2 + this->headerLineHeight, 0);
    manualObject->end();

    float bookmarkWidth = width / 2 - this->bookmarkFieldWidth;
    float newHeight = height / 2 + this->headerLineHeight;

    // ------------------------- BOOKMARK BUTTON -------------------------
    /*Ogre::ManualObject* bookmarkManualObject = elemGraphicsCasted->getBookmarkManualObject();
    bookmarkManualObject->begin(elem->getName() + "Bookmark_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->textureCoord(0, 0);
    bookmarkManualObject->position(bookmarkWidth, height / 2, 0);
    bookmarkManualObject->textureCoord(0, 1);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->textureCoord(1, 0);
    bookmarkManualObject->position(width / 2, height / 2, 0);
    bookmarkManualObject->textureCoord(1, 1);
    bookmarkManualObject->end();

    bookmarkManualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, height / 2, 0);
    bookmarkManualObject->position(width / 2, height / 2, 0);
    bookmarkManualObject->position(width / 2, newHeight, 0);
    bookmarkManualObject->position(bookmarkWidth, newHeight, 0);
    bookmarkManualObject->end();



    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Bookmark_texture", "General");

    std::ostringstream fragmentsCount;
    fragmentsCount << elemCasted->getCollectionFragmentsCount();

    UtilitiesDrawing::writeToTexture(
        fragmentsCount.str(),
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 1,
            this->textureSizeScale * this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        BOOKMARK_FONT.getPointer(),
        blackColour,
        'c',
        true);*/

    float typeWidth = 20;

    // ------------------------- TYPE FIELD -------------------------
    /*manualObject->begin(elem->getName() + "Type_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(bookmarkWidth, height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->position(bookmarkWidth, height / 2, 0);
    manualObject->position(bookmarkWidth, newHeight, 0);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Type_texture", "General");

    UtilitiesDrawing::writeToTexture(
        "Seq",
        texture,
        Ogre::Image::Box(
            0,
            this->textureSizeScale * 3,
            this->textureSizeScale * this->typeFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        TYPE_FONT.getPointer(),
        blueColour,
        'c',
        true);*/

    // ------------------------- CONDITION FIELD -------------------------
    float conditionWidth = - width / 2;

    manualObject->begin(elem->getName() + "Condition_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(conditionWidth - typeWidth/2, newHeight, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(conditionWidth- typeWidth/2, height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(typeWidth, newHeight, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(typeWidth, height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->position(conditionWidth, height / 2, 0);
    manualObject->position(conditionWidth + typeWidth - 5, height / 2, 0);
    manualObject->position(conditionWidth + typeWidth, height / 2+5, 0);
    manualObject->position(conditionWidth + typeWidth, newHeight, 0);
    manualObject->position(conditionWidth, newHeight, 0);
    manualObject->end();

    texture = Ogre::TextureManager::getSingleton().load(elem->getName() + "Condition_texture", "General");

    UtilitiesDrawing::writeToTexture(
        "Seq",
        texture,
        Ogre::Image::Box(
            this->textureSizeScale * 10,
            this->textureSizeScale * 2,
            this->textureSizeScale * width - this->typeFieldWidth - this->bookmarkFieldWidth,
            this->textureSizeScale * this->headerLineHeight),
        CONDITION_FONT.getPointer(),
        blackColour,
        'l',
        true);

    elemGraphicsCasted->getSceneNode()->attachObject( manualObject );
    //elemGraphicsCasted->getSceneNode()->attachObject( bookmarkManualObject );
}


void FragmentAlgorithm::select(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void FragmentAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}

void FragmentAlgorithm::initFonts()
{
    if (BOOKMARK_FONT.isNull())
    {
        BOOKMARK_FONT = Ogre::FontManager::getSingleton().create("Fragment_Bookmark_font", "General");
        BOOKMARK_FONT->setType(Ogre::FT_TRUETYPE);
        BOOKMARK_FONT->setSource("times.ttf");
        BOOKMARK_FONT->setTrueTypeSize(28);
        BOOKMARK_FONT->setTrueTypeResolution(96);
        BOOKMARK_FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        BOOKMARK_FONT->load();
    }

    if (TYPE_FONT.isNull())
    {
        TYPE_FONT = Ogre::FontManager::getSingleton().create("Fragment_Type_font", "General");
        TYPE_FONT->setType(Ogre::FT_TRUETYPE);
        TYPE_FONT->setSource("times.ttf");
        TYPE_FONT->setTrueTypeSize(22);
        TYPE_FONT->setTrueTypeResolution(96);
        TYPE_FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        TYPE_FONT->load();
    }

    if (CONDITION_FONT.isNull())
    {
        CONDITION_FONT = Ogre::FontManager::getSingleton().create("Fragment_Condition_font", "General");
        CONDITION_FONT->setType(Ogre::FT_TRUETYPE);
        CONDITION_FONT->setSource("times.ttf");
        CONDITION_FONT->setTrueTypeSize(18);
        CONDITION_FONT->setTrueTypeResolution(96);
        CONDITION_FONT->addCodePointRange(Ogre::Font::CodePointRange(33, 126));
        CONDITION_FONT->load();
    }
}

void FragmentAlgorithm::initTextures(Fragment* elem,float count)
{
    Ogre::TexturePtr texture;
    Ogre::Texture* background;

    // BOOKMARK FIELD
    texture = Ogre::TextureManager::getSingleton().createManual(
                  elem->getName() + "Bookmark_texture",
                  "General",
                  Ogre::TEX_TYPE_2D,
                  this->textureSizeScale * this->bookmarkFieldWidth,
                  this->textureSizeScale * this->headerLineHeight,
                  Ogre::MIP_UNLIMITED,
                  Ogre::PF_X8R8G8B8,
                  Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    background = Ogre::TextureManager::getSingleton().load("3D_material_white.png", "General").getPointer();
    texture->getBuffer()->blit(background->getBuffer()); // Draw the background to the new texture

    // TYPE FIELD
    texture = Ogre::TextureManager::getSingleton().createManual(
                  elem->getName() + "Type_texture",
                  "General",
                  Ogre::TEX_TYPE_2D,
                  this->textureSizeScale * this->typeFieldWidth,
                  this->textureSizeScale * this->headerLineHeight,
                  Ogre::MIP_UNLIMITED,
                  Ogre::PF_X8R8G8B8,
                  Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    background = Ogre::TextureManager::getSingleton().load("3D_material_white.png", "General").getPointer();
    texture->getBuffer()->blit(background->getBuffer()); // Draw the background to the new texture

    // CONDITION FIELD
    double width = static_cast<ContainerGraphics*>(elem->getGraphics())->getWidth();
    texture = Ogre::TextureManager::getSingleton().createManual(
                  elem->getName() + "Condition_texture",
                  "General",
                  Ogre::TEX_TYPE_2D,
                  this->textureSizeScale * (width - this->typeFieldWidth - this->bookmarkFieldWidth),
                  this->textureSizeScale * this->headerLineHeight,
                  Ogre::MIP_UNLIMITED,
                  Ogre::PF_X8R8G8B8,
                  Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    background = Ogre::TextureManager::getSingleton().load("3D_material_white.png", "General").getPointer();
    texture->getBuffer()->blit(background->getBuffer()); // Draw the background to the new texture

    for(int i=0;i<count;i++)
    {
        std::ostringstream strCount;
        strCount << i;
        texture = Ogre::TextureManager::getSingleton().createManual(
                      elem->getName() + "Clause_texture"+strCount.str(),
                      "General",
                      Ogre::TEX_TYPE_2D,
                      this->textureSizeScale * (width - this->typeFieldWidth - this->bookmarkFieldWidth)/1.1,
                      this->textureSizeScale * this->headerLineHeight*1.1,
                      Ogre::MIP_UNLIMITED,
                      Ogre::PF_X8R8G8B8,
                      Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);
        background = Ogre::TextureManager::getSingleton().load("3D_material_white.png", "General").getPointer();
        texture->getBuffer()->blit(background->getBuffer()); // Draw the background to the new texture
    }
}

void FragmentAlgorithm::initMaterials(Fragment* elem, Element* helpElement, float count)
{
    Ogre::MaterialPtr material;
    //elem->material = material;
    material = Ogre::MaterialManager::getSingleton().load("Fragment_type_material","Popular");
    material = material->clone(elem->getName() + "Type_material");
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "Type_texture");
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);


    material = Ogre::MaterialManager::getSingleton().load("Fragment_condition_material","Popular");
    material = material->clone(elem->getName() + "Condition_material");
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "Condition_texture");
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    helpElement->material = material;

    material = Ogre::MaterialManager::getSingleton().load("Fragment_bookmark_material","Popular");
    material = material->clone(elem->getName() + "Bookmark_material");
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "Bookmark_texture");
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

    for(int i=count-1;i>=0;i--)
    {
        std::ostringstream strCount;
        strCount << i;
        material = Ogre::MaterialManager::getSingleton().load("Condition_material","Popular");
        material = material->clone(elem->getName() + "Fragment_material"+strCount.str());
        material->getTechnique(0)->getPass(0)->createTextureUnitState(elem->getName() + "Clause_texture"+strCount.str());
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    }

}

void FragmentAlgorithm::cleanUp()
{
    BOOKMARK_FONT.setNull();
    TYPE_FONT.setNull();
    CONDITION_FONT.setNull();
}
