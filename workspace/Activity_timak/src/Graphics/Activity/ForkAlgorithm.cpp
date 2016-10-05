#include "ForkAlgorithm.h"

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

#include "../../Core/Activity/Fork.h"
#include "ForkGraphics.h"

#include "../../Core/Metamodel/include/Element.h"
#include "../../ApplicationManagement/ElementCollection.h"
#include "../../Core/Metamodel/include/ForkNode.h"

const double ForkAlgorithm::SIZE = 3;

ForkAlgorithm::ForkAlgorithm() : DrawingAlgorithm()
{
	setSize((int)ForkAlgorithm::SIZE);
}
ForkAlgorithm::~ForkAlgorithm()
{}

void ForkAlgorithm::draw(const std::string& A_name)
{

    std::pair<Element*, team4::MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);
    Fork* elemCasted;
    ForkGraphics* elemGraphicsCasted;

    if (elem.second->getType() != team4::ForkNode::ELEMENT_TYPE)
    {
        std::ostringstream os;
        os << "Invalid element type: ";
        os << "Expecting '";
        os << team4::ForkNode::ELEMENT_TYPE;
        os << "' instead of '";
        os << elem.second->getType();
        os << "'.";
        Ogre::LogManager::getSingleton().logMessage(os.str());

        return;
    }
    else
    {
        elemCasted = static_cast<Fork*>(elem.first);
        elemGraphicsCasted = static_cast<ForkGraphics*>(elem.first->getGraphics());
    }

    this->elem = elemCasted;
    this->elemGraphics = elemGraphicsCasted;

    double size = ForkAlgorithm::SIZE;
    double z = 0;

    Ogre::ManualObject* manualObject = elemGraphicsCasted->getManualObject();

    int width = size;
	int height = size *20;

	manualObject->begin(elem.second->getName() + "_material", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    manualObject->position(-height, width, z);
    manualObject->position(height, width, z);
    manualObject->position(-height, -width, z);
    manualObject->position(height, -width, z);
    manualObject->end();

    manualObject->begin("BaseLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
    manualObject->position(-height, width, z);
    manualObject->position(height, width, z);
    manualObject->position(-height, -width, z);
    manualObject->position(height, -width, z);
    manualObject->position(-height, width, z);
    manualObject->position(-height, -width, z);
    manualObject->position(height, width, z);
    manualObject->position(height, -width, z);
    manualObject->end();

    Ogre::SceneNode* node = elemGraphicsCasted->getSceneNode();
    node->attachObject(manualObject);

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(elem.second->getName() + "_material", "General");
    elem.first->material=material;
    material->getTechnique(0)->getPass(0)->createTextureUnitState(elem.second->getName() + "_texture");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_MODULATE);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);

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

    texture->getBuffer()->blit(background->getBuffer());
}

void ForkAlgorithm::select(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(true);
}
void ForkAlgorithm::unselected(Element* elem)
{
    Ogre::MaterialPtr material = elem->material;
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
}
double ForkAlgorithm::getFullSize()
{
    return ForkAlgorithm::SIZE;
}
