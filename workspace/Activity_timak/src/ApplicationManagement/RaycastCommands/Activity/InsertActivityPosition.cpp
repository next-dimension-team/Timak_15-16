/*
 * InsertActivityPosition.cpp
 *
 *  Created on: 17.2.2014
 *      Author: Schade
 */

#include "InsertActivityPosition.h"

#include <MyGUI_PointerManager.h>
#include <MyGUI_Singleton.h>
#include <MyGUI_Window.h>
#include <OgreMovableObject.h>
#include <OgreRay.h>
#include <OgreSceneNode.h>
#include <OgreSceneQuery.h>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <iterator>
#include <string>

#include "../../../Graphics/ElementGraphics.h"
#include "../../../Gui/Activity/ActivityWindow.h"
#include "../../ApplicationStateManager.h"
#include "../../DiagramContexts/ActivityDiagramContext.h"
#include "../../ElementCollection.h"
#include "../../GuiManager.h"
#include "../../InteractionManager.h"
#include "../../../Core/Metamodel/include/Element.h"

InsertActivityPosition::InsertActivityPosition()
{
    distance = -1;
}

InsertActivityPosition::~InsertActivityPosition()
{}

bool InsertActivityPosition::conditionsAccepted()
{
    return true;
}

// TODO: inaccurate!! - what if there are more containers in same distance?
bool InsertActivityPosition::check()
{
    Ogre::MovableObject* mo = InteractionManager::getInstance()->getActualMovable();
    if (!mo)
    {
        return false;
    }
    if (mo->getName().substr(0,6).compare("layer_") == 0 ||
            mo->getName().substr(0,9).compare("fragment_") == 0 ||
            mo->getName().substr(0,10).compare("container_") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InsertActivityPosition::action()
{}

bool InsertActivityPosition::stop()
{
    if (distance == -1)
    { // first container
        distance = InteractionManager::getInstance()->getRayResultIterator()->distance;
        //TODO TEAM4
        //containers.push_back(static_cast<Container*>(ElementCollection::getInstance()->findElement(InteractionManager::getInstance()->getActualMovable()->getName())));
        return false;
    }
    else
    {
        Ogre::Real newDistance = InteractionManager::getInstance()->getRayResultIterator()->distance;
        if (newDistance > distance)
            return true;
        else
        { // containers on same distance
            distance = newDistance;
            //TODO TEAM4
            //containers.push_back(static_cast<Container*>(ElementCollection::getInstance()->findElement(InteractionManager::getInstance()->getActualMovable()->getName())));
            return false;
        }
    }
}

void InsertActivityPosition::postProcessAction()
{
	std::pair<Container*, team4::MetamodelElement*> container = getSelectedContainer();
    InteractionManager::getInstance()->setActiveContainer(container.first);

    Ogre::Vector3 worldPos = InteractionManager::getInstance()->getRay().getPoint(distance);
    Ogre::Vector3 localPos = container.first->getGraphics()->getSceneNode()->convertWorldToLocalPosition(worldPos);

    GuiManager::getInstance()->hideOldCursor(); // temporary - hides only old cursor, but new appears
    ActivityDiagramContext* ctx = static_cast<ActivityDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());
    ctx->getActivityWindow()->setData(container.first, new Ogre::Vector2(localPos.x, localPos.y));
    ctx->getActivityWindow()->fillDefaultText();
    ctx->getActivityWindow()->getWidget()->setVisible(true);
    MyGUI::PointerManager::getInstance().setVisible(true);
}

std::pair<Container*, team4::MetamodelElement*> InsertActivityPosition::getSelectedContainer()
{
    std::vector<std::pair<Container*, team4::MetamodelElement*>>::iterator i = containers.begin();
    std::pair<Container*, team4::MetamodelElement*> container;

    while(i != containers.end())
    {
        if ( container ==  std::pair<Container*, team4::MetamodelElement*>(NULL, NULL) || container.first->findElementRecursive((*i).second->getName()).first != 0)
        {
            container = *i;
        }
        i++;
    }
    return container;
}

