/*
 * LayerBookmarkAlgorithm.cpp
 *
 *  Created on: 25.6.2013
 *      Author: Schade
 */

#include "LayerBookmarkAlgorithm.h"

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

#include "../Core/LayerBookmark.h"
#include "LayerBookmarkGraphics.h"

#include "../Core/Metamodel/include/Element.h"
#include "../ApplicationManagement/ElementCollection.h"


LayerBookmarkAlgorithm::LayerBookmarkAlgorithm() : DrawingAlgorithm()
{}
LayerBookmarkAlgorithm::~LayerBookmarkAlgorithm()
{}

void LayerBookmarkAlgorithm::draw(const std::string& A_name)
{
	std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
	Element* elem = element.first;
    std::cout << "LayerBookmarkAlgorithm::draw()  " << elem->getName() << "\n";
    return;
    LayerBookmark* elemCasted;
    LayerBookmarkGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != LayerBookmark::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << LayerBookmark::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<LayerBookmark*>(elem);
        elemGraphicsCasted = static_cast<LayerBookmarkGraphics*>(elem->getGraphics());
    }

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    double width = elemGraphicsCasted->getWidth();
    double height = elemGraphicsCasted->getHeight();
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
    material->getTechnique(0)->getPass(0)->createTextureUnitState("3D_material_4.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);

    try
    {
        elemGraphicsCasted->getSceneNode()->detachObject(manualObject);
        std::cout << "16. detach" <<std::endl;

    }
    catch(...)
    {
        std::cout << "17 catch." <<std::endl;
        return;
    }

    std::cout << "17 attach." <<std::endl;

    elemGraphicsCasted->getSceneNode()->attachObject(manualObject);


}

void LayerBookmarkAlgorithm::select(Element* elem)
{



    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void LayerBookmarkAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}
