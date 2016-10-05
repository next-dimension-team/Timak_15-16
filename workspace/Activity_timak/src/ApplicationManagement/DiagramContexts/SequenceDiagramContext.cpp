/*
 * SequenceDiagramContext.cpp
 *
 *  Created on: Nov 8, 2015
 *      Author: Matej
 */

#include "SequenceDiagramContext.h"
#include "MyGUI_Window.h"
#include "MyGUI_Button.h"
#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"
#include "MyGUI_InputManager.h"

#include "../DataManager.h"
#include "../GuiManager.h"
#include "../DrawManager.h"
#include "../../Main.h"
#include "../ElementCollection.h"

#include <OgreMaterialManager.h>
#include <OgrePrerequisites.h>
#include <OgreTextureManager.h>

SequenceDiagramContext::SequenceDiagramContext():  DiagramContext() {
	// TODO Auto-generated constructor stub
	tab_visible = false;
	edit_visible = false;
	lastClickedButton = "";
	//lay1 = NULL;

}

SequenceDiagramContext::~SequenceDiagramContext() {
	// TODO Auto-generated destructor stub
}

void SequenceDiagramContext::inicializeWidget(double A_width, double A_height)
{
    widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("ClassCreateResource", 0, 0, 50, 50, MyGUI::Align::Default, "Main", "ClassCreateWindow1");
}

void SequenceDiagramContext::activateGui()
{
		Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
	    /*activityWindow = new ActivityWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
	    activityWindow->getWidget()->setVisible(false);*/
	    inicializeWidget(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());

	    Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
	    OgreBites::SdkTrayManager* mTrayMgr = GuiManager::getInstance()->getTrayManager();
	    MyGUI::PointerManager::getInstance().setVisible(false);


	    /*_windowConnector = new ConnectorWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
	    _windowConnector->getWidget()->setVisible(false);*/

	    MyGUI::ResourceManager::getInstance().load("ButtonImage_sekv.resource");
	    MyGUI::LayoutManager::getInstance().loadLayout("menu_sekv.layout");
	    MyGUI::LayoutManager::getInstance().loadLayout("edit_sekv.layout");
	    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());


	    _windowConnector = new ConnectorWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
	    _windowConnector->getWidget()->setVisible(false);

	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("cancelButton"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("okButton"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_layer"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_layer_s"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_initial"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_activity"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_seq"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_alt"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_loop"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_dependency"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_export"));
	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_import"));

	    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_menu"));

	    for (int i=0; i < (int)_buttons.size(); i++)
	    {
	        _buttons[i]->eventMouseButtonClick += MyGUI::newDelegate(this, &SequenceDiagramContext::notifyMyGUImenu);
	    }
	    _buttons.back()->setPosition(mCamera->getViewport()->getActualWidth()-60,10);


	    MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
	    editWidget->setVisible(edit_visible);

	    MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
	    widget->setVisible(tab_visible);
	    widget->setPosition(mCamera->getViewport()->getActualWidth()-290,30);


	    mCamera->setPosition(Ogre::Vector3(0,200,500));
	    mCamera->lookAt(Ogre::Vector3(0,0,0));

}

void SequenceDiagramContext::initContent()
{
    DataManager* dataM = DataManager::getInstance();
}


void SequenceDiagramContext::releaseContent()
{
	 Main::sMSceneMgr->clearScene();

	 DrawManager::getInstance()->init(Main::sMSceneMgr);
	 ElementCollection::getInstance()->removeAllElements();


	for (int i=0; i < (int)_buttons.size(); i++)
	{
		MyGUI::Gui::getInstance().destroyWidget(_buttons[i]);
	}
	MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
	MyGUI::Gui::getInstance().destroyWidget(widget);

	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
	MyGUI::Gui::getInstance().destroyWidget(editWidget);

	//MyGUI::Gui::getInstance().destroyWidget(_activityWindow->getWidget());
	MyGUI::Gui::getInstance().destroyWidget(_windowConnector->getWidget());

	DataManager::getInstance()->resetFactories();
}

void SequenceDiagramContext::notifyKeyboardButton(OIS::KeyCode key)
{
	Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();

	if (key == OIS::KC_ESCAPE){

		tab_visible = false;
		edit_visible = false;
	}

	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
	editWidget->setVisible(edit_visible);

	MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
	widget->setVisible(tab_visible);
	widget->setPosition(mCamera->getViewport()->getActualWidth()-290,30);
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
}

void SequenceDiagramContext::notifyMyGUImenu(MyGUI::Widget * _sender)
{

	 if (_sender->getName() == "button_menu")
	    {
	        if (tab_visible == true)
	        {
	            tab_visible = false;
	        }
	        else
	        {
	            tab_visible = true;
	        }
	 }

    DataManager* dataM = DataManager::getInstance();
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    /*
    MyGUI::Widget* widget1 = MyGUI::Gui::getInstance().findWidgetT("Note1");
    if (_sender->getName() == "button_layer_s" && lastClickedButton == "button_layer_s")
    {
        lastClickedButton = "";
    }
    else
    {
        lastClickedButton = _sender->getName();
    }
    if (lastClickedButton == "button_layer_s")
    {
        DrawManager::getInstance()->DrawSelectedLayers();
        widget1->setVisible(true);
    }
    else
    {
        DrawManager::getInstance()->DrawNormalLayers();
        widget1->setVisible(false);
    }
    std::cout<<"clicked "+ _sender->getName() + " FF"+ lastClickedButton<<std::endl;
    if (_sender->getName() == "button_export")
    {
        team4::Serializer ser;
        ser.run();
        return;
    }
    else if (_sender->getName() == "button_import")
    {
        //team4::Deserializer deser;
        //deser.run();
        return;
    }
    if (_sender->getName() == "button_layer")
    {
        lay1 = dataM->createLayer();
    }
    else if (_sender->getName() == "Dependency")
    {
        if(selectedElements.size() == 2 && selectedElements[0].first !=NULL && selectedElements[1].first != NULL)
        {
            if (selectedElements[0].first->getType().compare( "DecisionNode" )==0)
            {
                typeOfElement = "edge";
                MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
                edit_visible = true;
                editWidget->setVisible(edit_visible);
                std::ostringstream inputStringStream;
                if (decision)
                    inputStringStream << "YES";
                else
                    inputStringStream << "NO";
                inputString = inputStringStream.str();
                MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
                textBoxWidget->setProperty("Wiget_Caption", inputString);
            }
            else
            {
                DataManager::getInstance()->createFlow(selectedElements[0].second->getName(), selectedElements[1].second->getName(), "");
                lastClickedButton = "";
            }
            clearSelection();
        }
    }
    else if (_sender->getName() == "button_menu")
    {
        if (tab_visible == true)
        {
            tab_visible = false;
        }
        else
        {
            tab_visible = true;
        }
    }


    if(_sender->getName() == "okButton")
    {
        edit_visible = false;
        if(typeOfElement.compare("activity")==0)
        {
            dataM->createActivity(lay1, inputString, elementVector);
            typeOfElement = "";
        }
        else if(typeOfElement.compare("edge") == 0)
        {
            DataManager::getInstance()->createFlow(selectedElements[0].second->getName(), selectedElements[1].second->getName(), inputString);
            decision = !decision;
            typeOfElement = "";
        }
        else if(typeOfElement.compare("seq")==0)
        {
        	if (fragmentPos==-1)
        	{
        		width = atoi(inputString.c_str());
                dataM->createFragment(lay1, elementVector);
        		fragmentPos = -3;
        		fragmentVector.clear();
        		typeOfElement = "";
        		width = 0;
        		height = 0;
        	}
        	else if (fragmentPos == -2)
        	{
        		height = atoi(inputString.c_str());
        		fragmentPos++;
        		typeOfElement = "seq";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		stringstream ss;
        		ss << height;
        		inputString = ss.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
        		editWidget->setProperty("Widget_Caption", "Set width");
        	}
        }
        else if(typeOfElement.compare("loop")==0)
        {
            if (fragmentPos == 1)
            {
                fragmentVector.push_back(inputString);
                dataM->createLoop(lay1,elementVector,fragmentVector[0],fragmentVector[1],width,height);
                fragmentPos = -3;
                fragmentVector.clear();
                typeOfElement = "";
                width = 0;
                height = 0;
            }
            else if (fragmentPos==-1)
            {
            	width = atoi(inputString.c_str());
            	fragmentPos++;
            	typeOfElement = "loop";
            	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
            	edit_visible = true;
            	inputString = "Init";
            	MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
            	textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set name");
            }
            else if (fragmentPos == -2)
            {
            	height = atoi(inputString.c_str());
            	fragmentPos++;
            	typeOfElement = "loop";
            	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
            	edit_visible = true;
            	stringstream ss;
            	ss << width;
            	inputString = ss.str();
            	MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
            	textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set width");
            }
            else
            {
                fragmentVector.push_back(inputString);
                fragmentPos++;
                typeOfElement= "loop";
                MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
                edit_visible = true;
                editWidget->setVisible(edit_visible);
                inputString = "Cond";
                MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
                textBoxWidget->setProperty("Widget_Caption", inputString);
            }
        }
        else if (typeOfElement.compare("alt") == 0)
        {
        	if (fragmentPos==-1)
        	{
        		width = atoi(inputString.c_str());
        		fragmentPos++;
        		typeOfElement = "alt";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		std::ostringstream inputStringStream;
        		inputStringStream << "Alt " << fragmentPos;
        		inputString = inputStringStream.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set name");
        	}
        	else if (fragmentPos == -2)
        	{
        		height = atoi(inputString.c_str());
        		fragmentPos++;
        		typeOfElement = "alt";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		stringstream ss;
        		ss << height;
        		inputString = ss.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
        		editWidget->setProperty("Widget_Caption", "Set width");
        	}
        	else
        	{
        		fragmentVector.push_back(inputString);
        		fragmentPos++;
        		typeOfElement = "alt";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		editWidget->setVisible(edit_visible);
        		std::ostringstream inputStringStream;
        		inputStringStream << "Alt " << fragmentPos;
        		inputString = inputStringStream.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
        	}
        }
        lastClickedButton = "";
    }
    else if(lastClickedButton == "cancelButton")
    {
        edit_visible = false;
        std::ostringstream inputStringStream;
        if(typeOfElement.compare("activity")==0)
        {
            inputStringStream << "Activity " << activity;
            inputString = inputStringStream.str();
            dataM->createActivity(lay1, inputString, elementVector);
            typeOfElement = "";
        }
        else if(typeOfElement.compare("edge") == 0)
        {
            DataManager::getInstance()->createFlow(selectedElements[0].second->getName(), selectedElements[1].second->getName(), decision?"YES":"NO");
            decision = !decision;
            typeOfElement = "";
        }
        else if(typeOfElement.compare("seq") == 0)
        {
        	if (fragmentPos == -2)
        	{
        		fragmentPos++;
        		typeOfElement = "seq";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		stringstream ss;
        		ss << width;
        		inputString = ss.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
        		editWidget->setProperty("Widget_Caption", "Set width");
        	}
        	else
        	{
        		width = atoi(inputString.c_str());
        		dataM->createFragment(lay1, elementVector);
        		typeOfElement = "";
        		fragmentPos = -3;
        		width = 0;
        		height = 0;
        		fragmentVector.clear();
        	}
        }
        else if (typeOfElement.compare("loop") == 0)
        {
            if (fragmentPos == 1)
            {
                fragmentVector.push_back("Cond");
                int width = ElementCollection::getInstance()->getDefaultWidthOfFragment(elementVector);
                int height = ElementCollection::getInstance()->getDefaultHeightOfFragment(elementVector);
                Ogre::Vector2* point= ElementCollection::getInstance()->getDefaultCenterOfFragment(elementVector);
                dataM->createLoop(lay1,point,fragmentVector[0],fragmentVector[1],width,height);
                fragmentPos = -3;
                height = 0;
                width = 0;
                fragmentVector.clear();
                typeOfElement = "";
            }
            else if (fragmentPos==-1)
            {
            	fragmentPos++;
            	typeOfElement = "loop";
            	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
            	edit_visible = true;
            	inputString = "Init";
            	MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
            	textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set name");
            }
            else if (fragmentPos == -2)
            {
            	fragmentPos++;
            	typeOfElement = "loop";
            	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
            	edit_visible = true;
            	stringstream ss;
            	ss << width;
            	inputString = ss.str();
            	MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
            	textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set width");
            }
            else
            {
                fragmentVector.push_back("Init");
                fragmentPos++;
                typeOfElement= "loop";
                MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
                edit_visible = true;
                editWidget->setVisible(edit_visible);
                inputString = "Cond";
                MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
                textBoxWidget->setProperty("Widget_Caption", inputString);
            }
        }
        else if (typeOfElement.compare("alt") == 0)
        {
        	if (fragmentPos==-1)
        	{
        		fragmentPos++;
        		typeOfElement = "alt";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		std::ostringstream inputStringStream;
        		inputStringStream << "Alt " << fragmentPos;
        		inputString = inputStringStream.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
            	editWidget->setProperty("Widget_Caption", "Set name");
        	}
        	else if (fragmentPos == -2)
        	{
        		fragmentPos++;
        		typeOfElement = "alt";
        		MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        		edit_visible = true;
        		stringstream ss;
        		ss << width;
        		inputString = ss.str();
        		MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        		textBoxWidget->setProperty("Widget_Caption", inputString);
        		editWidget->setProperty("Widget_Caption", "Set width");
        	}
        	else
        	{
        		dataM->createAlt(lay1, elementVector, fragmentVector);
        		typeOfElement = "";
        		fragmentPos = -3;
        		width = 0;
        		height = 0;
        		fragmentVector.clear();
        	}
        }
        lastClickedButton = "";
        inputString = "";
    }
  */
    MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
    MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");

    editWidget->setVisible(edit_visible);
    widget->setVisible(tab_visible);
    DrawManager::getInstance()->drawAll();
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    DEF_END;

}


void SequenceDiagramContext::notifyMouseButtonClick(MyGUI::Widget * _sender,  OIS::MouseButtonID id)
{
    /*
    DEF_BEGIN;
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    //if (id != OIS::MB_Right)
    {
        //clearSelection();
    }
    if (_sender->getName() == "Remove_All")
    {
        clearSelection();
    }


    DrawManager::getInstance()->drawAll();
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    DEF_END;
    */
}


