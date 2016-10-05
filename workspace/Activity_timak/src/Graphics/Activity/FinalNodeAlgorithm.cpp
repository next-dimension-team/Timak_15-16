/*
 * FinalNodeAlgorithm.cpp
 *
 *  Created on: 22.10.2013
 *      Author: Schade
 */

#include "FinalNodeAlgorithm.h"

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

#include "../../Core/Activity/FinalNode.h"

#include "NodeGraphics.h"
#include "../../HelperTeam4.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../Core/Metamodel/include/FinalNode.h"
#include "../../ApplicationManagement/ElementCollection.h"

FinalNodeAlgorithm::FinalNodeAlgorithm() : DrawingAlgorithm()
{}
FinalNodeAlgorithm::~FinalNodeAlgorithm()
{}

const double FinalNodeAlgorithm::SIZE = 20;

void FinalNodeAlgorithm::draw(const std::string& A_name)
{
	std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
	Element* elem = element.first;

    ::FinalNode* elemCasted;
    NodeGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != team4::FinalNode::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << team4::FinalNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<FinalNode*>(elem);
        elemGraphicsCasted = static_cast<NodeGraphics*>(elem->getGraphics());
    }

    this->elem = elemCasted;
    this->elemGraphics = elemGraphicsCasted;


    // circle coordinates precalculation
    double radius = FinalNodeAlgorithm::SIZE / 2;
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
    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_FAN);

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

    // border drawing
    manualObject->begin("SolidBlackMaterial", Ogre::RenderOperation::OT_LINE_STRIP);
    for (int i = resolution - 1; i >= 0; --i)
    {
        manualObject->position(coords[i][0] / 3, coords[i][1] / 3, z);
    }
    manualObject->position(coords[resolution - 1][0] / 3, coords[resolution - 1][1] / 3, z); // connect last point to first
    manualObject->end();

    // MATERIAL
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem->getName() + "_material", "General");
    elem->material = material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState("3D_material_2.png");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);

    elemGraphicsCasted->getSceneNode()->attachObject(manualObject);
}
void FinalNodeAlgorithm::select(Element* elem)
{



    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void FinalNodeAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}
double FinalNodeAlgorithm::getFullSize()
{
    return FinalNodeAlgorithm::SIZE;
}

