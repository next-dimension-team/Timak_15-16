/*
 * ModifyState.cpp
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#include "ModifyState.h"

#include <OgreLogManager.h>
#include <OISPrereqs.h>
#include <SdkTrays.h>
#include <typeinfo>

#include "MyGUI.h"
#include "MyGUI_Button.h"
#include "MyGUI_Widget.h"
#include "../../Core/Layer.h"
#include "../../Core/LayerBookmark.h"
#include "../../Gui/Activity/Popup.h"
#include "../ApplicationStateManager.h"
#include "../DataManager.h"
#include "../DiagramContexts/ActivityDiagramContext.h"
#include "../DiagramContexts/ClassDiagramContext.h"
#include "../DiagramContexts/SequenceDiagramContext.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../GuiManager.h"
#include "../InteractionManager.h"
#include "../RaycastCommands/ActivateFragment.h"
#include "Activity/InsertActivityState.h"
#include "InsertClassState.h"
#include "InsertConnectorState.h"
#include "ViewState.h"
#include "../Mvc/Gui.h"
#include <math.h>

ModifyState::ModifyState(ApplicationState* parentState) : ApplicationState(parentState)
{}
ModifyState::~ModifyState()
{}

void ModifyState::init()
{
    GuiManager::getInstance()->showCursor();
}

void ModifyState::processButton(OIS::KeyCode key)
{
	team4::Gui* ctxActivity = dynamic_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext());
	SequenceDiagramContext* ctxSequence = dynamic_cast<SequenceDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());

    if (key == OIS::KC_SPACE || key == OIS::KC_ESCAPE)
    {
        this->setState(typeid(ViewState).name());
    }
    if (ctxActivity != 0)
    {
    	ctxActivity->notifyKeyboardButton(key);
    }

    if (ctxSequence != 0)
    {
    	ctxSequence->notifyKeyboardButton(key);
    }
}

void ModifyState::processClick(OIS::MouseEvent arg, OIS::MouseButtonID id)
{
	DEF_BEGIN;
    ClassDiagramContext* ctxClass = dynamic_cast<ClassDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());
    if (ctxClass != 0)
    {
        if (ctxClass->getClassButtonState() == OgreBites::BS_OVER)
        {
            DrawManager::getInstance()->setBookmarksVisibility(true);
            InteractionManager::getInstance()->setActiveLayer(0);
            this->setState(typeid(InsertClassState).name());
            return;
        }
        if (ctxClass->getConnectionButtonState() == OgreBites::BS_OVER)
        {
            DrawManager::getInstance()->setBookmarksVisibility(true);
            InteractionManager::getInstance()->setActiveLayer(0);
            this->setState(typeid(InsertConnectorState).name());
            return;
        }
        if (ctxClass->getLayerButtonState() == OgreBites::BS_OVER)
        {
        	// TODO TEAM4
            /*// TODO: Make layer adding more sophisticated
            Layer* lay = DataManager::getInstance()->createLayer();
            lay->draw();
            ElementCollection::getInstance()->findBookmark(lay->getName())->draw();
            DrawManager::getInstance()->setBookmarksVisibility(false); // TODO: find better solution?
            this->setState(typeid(ViewState).name());*/
            return;
        }
    }

    //ActivityDiagramContext* ctxActivity = dynamic_cast<ActivityDiagramContext*>(ApplicationStateManager::getInstance()->getDiagramContext());
    team4::Gui* ctxActivity = dynamic_cast<team4::Gui*>(ApplicationStateManager::getInstance()->getDiagramContext());

    if (ctxActivity != 0)
    {
        if (!Popup::isActive())
        {
        	MyGUI::Widget* button  = ctxActivity->getButtonWithState();
        	if (button != NULL)
        	{
        		ctxActivity->notifyMouseButtonClick(button, id);
        		return;
        	}
            if (id == OIS::MB_Left)
            {
                InteractionManager::getInstance()->rayCast(arg.state, new ActivateFragment());
            }
            else if (id == OIS::MB_Right)
            {
                Popup::displayPopup(arg.state.X.abs, arg.state.Y.abs);
            }
            if(button == NULL)
            {
				Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
				Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(  arg.state.X.abs/float(arg.state.width), arg.state.Y.abs/float(arg.state.height) );
				//Ogre::Ray mouseRay = InteractionManager::getInstance()->getRay();
				//Ogre::Real newDistance = InteractionManager::getInstance()->getRayResultIterator()->distance;
				//Ogre::Vector3 point = mouseRay.getPoint(0);
				//Ogre::Vector3 worldPos = InteractionManager::getInstance()->getRay().getPoint(InteractionManager::getInstance()->getRayResultIterator()->distance);
				//Ogre::Vector3 localPos = ElementCollection::getInstance()->getSelectedLayer()->getGraphics()->getSceneNode()->convertWorldToLocalPosition(worldPos);
				//Ogre::Vector3 point1 = ElementCollection::getInstance()->getSelectedLayer()->getGraphics()->getSceneNode()->convertWorldToLocalPosition(Ogre::Vector3(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs - 200));
				//ctxActivity->notifyMouseClick(point.x, point.y, id);
				Layer* layer = ElementCollection::getInstance()->getSelectedLayer();
				int posun = 0;
				if (layer != NULL)
				{
					posun = layer->getId();
				}


				//float a = 500 + 200*posun;
				//float b = arg.state.X.abs;
				//float beta = acos((a)/sqrt(pow(a+200,2)+pow(b,2)));
				//float b1 = tan(beta)*a;

				float offset_x = 0;
				float offset_y = 0;
				if(posun > 0)
				{
					offset_x = 40 * float(pow(0.75,posun)-1)/float(0.75-1);
					offset_y = 30 * float(pow(0.75,posun)-1)/float(0.75-1);
				}
				float point_x = arg.state.X.abs-(arg.state.width)/2;
				//std::cout << "Point X pred: " << point_x << std::endl;
				if(point_x > 0)
				{
					float offset1_x = float(fabs(float(point_x)/float(200-offset_x)));
					point_x = point_x + offset_x * offset1_x;
				}
				else
				{
					float offset1_x = float(fabs(float(point_x)/float(200-offset_x)));
					point_x = point_x - offset_x * offset1_x;
				}
				float point_y = (arg.state.height)/2 -arg.state.Y.abs;
				//std::cout << "Point Y pred: " << point_y << std::endl;
				if(point_y > 0)
				{
					float offset1_y = float(fabs(float(point_y)/float(150-offset_y)));
					point_y = point_y + offset_y * offset1_y;
				}
				else
				{
					float offset1_y = float(fabs(float(point_y)/float(150-offset_y)));
					point_y = point_y - offset_y * offset1_y;
				}

				//std::cout << "Coordinates: x:" << point_x << " y:" << point_y << " z:" << point1.z << std::endl;
				//ctxActivity->notifyMouseClick(arg.state.X.abs-float(arg.state.width)/2, float(arg.state.height)/2 - arg.state.Y.abs, id );
				//std::cout << "x:" << point_x << " y:" << point_y << " z:" << point1.z << std::endl;
				ctxActivity->notifyMouseClick(point_x, point_y, id );
            }

        }
    }
    DEF_END;
}

void ModifyState::initInternalStates()
{
    currentInternalState = 0;
}

void ModifyState::processMessage(Message message)
{
    if (message.getEnumValue() == Message::Popup_Insert)
    {
        this->setState(typeid(InsertActivityState).name());
    }
    else if (message.getEnumValue() == Message::Popup_Modify)
    {
        // TODO: Activity modify
    }
    else if (message.getEnumValue() == Message::Popup_Delete)
    {
        // TODO: Activity delete
    }
    else
    {
        Ogre::LogManager::getSingleton().logMessage("ModifyState: Message not recognized!!");
    }
}
