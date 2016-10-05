/*
 * DecisionAlgorithm.cpp
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#include "DecisionAlgorithm.h"

#include <math.h>
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

#include "../../Core/Activity/Decision.h"
#include "DecisionGraphics.h"

#include "../../Core/Element.h"
#include "../../Core/Utilities.h"
#include "DecisionAlgorithm.h"
#include "../../HelperTeam4.h"

#include "../../Core/Activity/Decision.h"
#include "DecisionGraphics.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Metamodel/include/DecisionNode.h"



const double DecisionAlgorithm::SIZE = 20;

DecisionAlgorithm::DecisionAlgorithm() : DrawingAlgorithm()
{}
DecisionAlgorithm::~DecisionAlgorithm()
{}

void DecisionAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);

    DecisionGraphics* elemGraphicsCasted;

    // Cast control
    if (elem.second->getType() != team4::DecisionNode::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << team4::DecisionNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem.second->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemGraphicsCasted = static_cast<DecisionGraphics*>(elem.first->getGraphics());
    }
    this->elemGraphics = elemGraphicsCasted;


    double size = DecisionAlgorithm::SIZE / 2;
    double z = 0;


    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();

    manualObject->begin(elem.second->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(0, -size, z);
    manualObject->position(-size, 0, z);
    manualObject->position(size, 0, z);
    manualObject->position(0, size, z);

    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    manualObject->position(-size, 0, z);
    manualObject->position(0, -size, z);
    manualObject->position(size, 0, z);
    manualObject->position(0, size, z);
    manualObject->position(-size, 0, z);
    manualObject->end();

    Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
    node->attachObject(manualObject);


    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem.second->getName() + "_material", "General");
    elem.first->material=material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem.second->getName() + "_texture");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_REPLACE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);


    // TEXTURE
    double textureSizeScale = 5;
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
                                   elem.second->getName() + "_texture",
                                   "General",
                                   Ogre::TEX_TYPE_2D,
                                   textureSizeScale * sqrt(2*pow(size,2)),
                                   textureSizeScale * sqrt(2*pow(size,2)),
                                   Ogre::MIP_UNLIMITED,
                                   Ogre::PF_X8R8G8B8,
                                   Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_3.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());
}
void DecisionAlgorithm::select(Element* elem)
{



    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void DecisionAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}
double DecisionAlgorithm::getFullSize()
{
    return DecisionAlgorithm::SIZE;
}
