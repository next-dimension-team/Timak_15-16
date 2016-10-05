#include "MergeAlgorithm.h"

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

#include "../../Core/Activity/Merge.h"
#include "MergeGraphics.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"

const double MergeAlgorithm::SIZE = 20;

MergeAlgorithm::MergeAlgorithm() : DrawingAlgorithm()
{}
MergeAlgorithm::~MergeAlgorithm()
{}

void MergeAlgorithm::draw(const std::string& A_name)
{
    std::pair<Element*, team4::MetamodelElement*> element = ElementCollection::getInstance()->findElement(A_name);
    Element* elem = element.first;
    Merge* elemCasted;
    MergeGraphics* elemGraphicsCasted;

    // Cast control
    if (elem->getType() != Merge::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << Merge::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem->getType();
        os << "'.";

        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Merge*>(elem);
        elemGraphicsCasted = static_cast<MergeGraphics*>(elem->getGraphics());
    }

    this->elem = elemCasted;
    this->elemGraphics = elemGraphicsCasted;


    double size = MergeAlgorithm::SIZE / 2;
    double z = 0;


    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();

    manualObject->begin(elem->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
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
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem->getName() + "_material", "General");
    elem->material = material;
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
                                   textureSizeScale * sqrt(2*pow(size,2)),
                                   textureSizeScale * sqrt(2*pow(size,2)),
                                   Ogre::MIP_UNLIMITED,
                                   Ogre::PF_X8R8G8B8,
                                   Ogre::TU_STATIC|Ogre::TU_AUTOMIPMAP);

    Ogre::Texture* background = Ogre::TextureManager::getSingleton().load("3D_material_3.png", "General").getPointer();

    // Draw the background to the new texture
    texture->getBuffer()->blit(background->getBuffer());
}

void MergeAlgorithm::select(Element* elem)
{



    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);


}
void MergeAlgorithm::unselected(Element* elem)
{

    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

}

double MergeAlgorithm::getFullSize()
{
    return MergeAlgorithm::SIZE;
}
