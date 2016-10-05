/*
 * ContainerAlgorithm.cpp
 *
 *  Created on: 14.10.2013
 *      Author: Schade
 */

#include "ContainerAlgorithm.h"

#include <OgreBlendMode.h>
#include <OgreCommon.h>
#include <OgreHardwarePixelBuffer.h>
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

#include "../Core/Container.h"
#include "ContainerGraphics.h"
#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"

ContainerAlgorithm::ContainerAlgorithm() : DrawingAlgorithm()
{
    elem = NULL;
    elemGraphics = NULL;
}
ContainerAlgorithm::~ContainerAlgorithm()
{}

void ContainerAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Container* elemCasted;
    ContainerGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Container::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Container::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Container*>(elem);
        elemGraphicsCasted = static_cast<ContainerGraphics*>(elem->getGraphics());
    }

    this->elem = elemCasted;
    this->elemGraphics = elemGraphicsCasted;


    double finalWidth = 150;
    double finalHeight = 100;
    double x1 = - finalWidth/2;
    double x2 = finalWidth/2;
    double y1 = finalHeight/2;
    double y2 = - finalHeight/2;
    double z = 0;

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(x1, y1, z); //manualObject->textureCoord(0, 1);
    manualObject->position(x2, y1, z); //manualObject->textureCoord(1, 1);
    manualObject->position(x1, y2, z); //manualObject->textureCoord(0, 0);
    manualObject->position(x2, y2, z); //manualObject->textureCoord(1, 0);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
    manualObject->position(x1, y1, z);
    manualObject->position(x1, y2, z);
    manualObject->position(x1, y2, z);
    manualObject->position(x2, y2, z);
    manualObject->position(x2, y2, z);
    manualObject->position(x2, y1, z);
    manualObject->position(x2, y1, z);
    manualObject->position(x1, y1, z);
    manualObject->end();

    Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
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

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_4.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());
}
