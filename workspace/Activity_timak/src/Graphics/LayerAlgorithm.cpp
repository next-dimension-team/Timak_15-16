/*
 * LayerAlgorithm.cpp
 *
 *  Created on: 24.6.2013
 *      Author: Schade
 */

#include "LayerAlgorithm.h"

#include <OgreBlendMode.h>
#include <OgreCommon.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgrePass.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreTechnique.h>
#include <sstream>
#include <string>

#include "../Core/Layer.h"
#include "LayerGraphics.h"
#include "../HelperTeam4.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"


LayerAlgorithm::LayerAlgorithm() : DrawingAlgorithm()
{}
LayerAlgorithm::~LayerAlgorithm()
{}

void LayerAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Layer* elemCasted;
    LayerGraphics* elemGraphicsCasted;
    // Cast control
    if (elem->getType() != Layer::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Layer::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());
        return;
    }
    else
    {
        elemCasted = static_cast<Layer*>(elem);
        elemGraphicsCasted = static_cast<LayerGraphics*>(elem->getGraphics());
    }
    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();

    float width = elemGraphicsCasted->getWidth();
    float height = elemGraphicsCasted->getHeight();
    manualObject->setDynamic(true);
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-width / 2, height / 2, 0);
    manualObject->textureCoord(0, 0);
    manualObject->position(-width / 2, -height / 2, 0);
    manualObject->textureCoord(0, 1);
    manualObject->position(width / 2, height / 2, 0);
    manualObject->textureCoord(1, 0);
    manualObject->position(width / 2, -height / 2, 0);
    manualObject->textureCoord(1, 1);
    manualObject->end();
    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem->getName() + "_material", "General");
    elem->material = material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState("3D_UML_Layer.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    elemGraphicsCasted->getSceneNode()->attachObject(manualObject);
}

void LayerAlgorithm::select(Element* elem)
{
    DEF_BEGIN;


    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void LayerAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}

