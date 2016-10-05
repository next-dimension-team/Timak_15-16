/*
 * InitialNodeAlgorithm.cpp
 *
 *  Created on: 21.10.2013
 *      Author: Schade
 */

#include "InitialNodeAlgorithm.h"

#include <OgreBlendMode.h>
#include <OgreCommon.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMath.h>
#include <OgrePass.h>
#include <OgrePrerequisites.h>
#include <OgreRenderOperation.h>
#include <OgreSceneNode.h>
#include <OgreTechnique.h>
#include <sstream>
#include <string>

#include "../../Core/Activity/InitialNode.h"
#include "NodeGraphics.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Metamodel/include/InitialNode.h"

const double InitialNodeAlgorithm::SIZE = 20;

InitialNodeAlgorithm::InitialNodeAlgorithm() : DrawingAlgorithm()
{}
InitialNodeAlgorithm::~InitialNodeAlgorithm()
{}

void InitialNodeAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);
    NodeGraphics* elemGraphicsCasted;

    // Cast control
    if (elem.second->getType() != team4::InitialNode::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << team4::InitialNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem.second->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemGraphicsCasted = static_cast<NodeGraphics*>(elem.first->getGraphics());
    }

    this->elemGraphics = elemGraphicsCasted;


    // circle coordinates precalculation
    double radius = InitialNodeAlgorithm::SIZE / 2;
    double z = 0;
    int resolution = 36;

    Ogre::Real coords[resolution][2];
    Ogre::Degree alpha = (Ogre::Degree) 360 / resolution;
    Ogre::Degree theta = (Ogre::Degree) 0;

    for (int i = 0; i < resolution; ++i)
    {
        theta += alpha;

        coords[i][0] = Ogre::Math::Sin(theta) * radius; // X
        coords[i][1] = Ogre::Math::Cos(theta) * radius; // Y
    }


    // circle drawing
    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();
    manualObject->begin(elem.second->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_FAN);

    manualObject->position(0, 0, z);
    for (int i = resolution - 1; i >= 0; --i)
    {
        manualObject->position(coords[i][0], coords[i][1], z);
    }
    manualObject->position(coords[resolution - 1][0], coords[resolution - 1][1], z); // connect last point to first
    manualObject->end();

    // border drawing
    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    for (int i = resolution - 1; i >= 0; --i)
    {
        manualObject->position(coords[i][0], coords[i][1], z);
    }
    manualObject->position(coords[resolution - 1][0], coords[resolution - 1][1], z); // connect last point to first
    manualObject->end();

    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem.second->getName() + "_material", "General");
    elem.first->material = material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState("3D_material_5.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);
    elemGraphicsCasted->getSceneNode()->attachObject(manualObject);
}

double InitialNodeAlgorithm::getFullSize()
{
    return InitialNodeAlgorithm::SIZE;
}

void InitialNodeAlgorithm::select(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);
}
void InitialNodeAlgorithm::unselected(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}

