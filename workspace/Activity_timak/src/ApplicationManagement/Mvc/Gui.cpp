#include "Gui.h"
#include <iostream>

#include "../../HelperTeam4.h"

#include <OgreMaterialManager.h>
#include <OgrePrerequisites.h>
#include <OgreTextureManager.h>


#include "../../Core/Activity/Activity.h"
#include "../../Core/Activity/Decision.h"
#include "../../Core/Activity/Merge.h"
#include "../../Core/Activity/Fork.h"
#include "../../Core/Activity/Join.h"
#include "../../Core/Activity/FinalNode.h"
#include "../../Core/Activity/Fragment.h"
#include "../../Core/Activity/InitialNode.h"
#include "../../Core/Layer.h"
#include "../../Gui/Activity/ActivityWindow.h"
#include "../../Gui/ConnectorWindow.h"
#include "../../Main.h"
#include "../DataManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../GuiManager.h"
#include "../../Core/Class.h"

#include "../../Gui/ConnectorWindow.h"
#include "../../Main.h"
#include "../DataManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../GuiManager.h"

#include "MyGUI_Window.h"
#include "MyGUI_Button.h"
#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"
#include "MyGUI_InputManager.h"

#include "../ControlerMetamodel.h"
#include "../GuiManager.h"

#include "../InteractionManager.h"
#include "../Metamodel.h"
#include "../../Core/Metamodel/include/Element.h"
#include "../../Serialization/Serializer.h"
#include "../../Serialization/Deserializer.h"

using MyGUI::Window;

int activity = 0;
std::string typeOfElement = "";
bool decision = true;
Ogre::Vector2 *elementVector;
std::string inputString;
int fragmentPos = -3;
std::vector<std::string> fragmentVector;
int width = 0;
int height = 0;

namespace team4
{
Gui::Gui()
{
    _activityWindow = NULL;
    _windowConnector = NULL;
    button = NULL;
    editBox = NULL;
    mGUI = NULL;
    lay1 = NULL;
    widget = NULL;
    lastClickedButton = "";
    tab_visible = false;
    edit_visible = false;
}

void Gui::inicializeWidget(double A_width, double A_height)
{
    widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("ClassCreateResource", 0, 0, 50, 50, MyGUI::Align::Default, "Main", "ClassCreateWindow1");
}

Gui::~Gui()
{}

void Gui::refresh()
{}

void Gui::activateGui()
{
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    _activityWindow = new ActivityWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    _activityWindow->getWidget()->setVisible(false);
    inicializeWidget(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());

    Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
    OgreBites::SdkTrayManager* mTrayMgr = GuiManager::getInstance()->getTrayManager();
    MyGUI::PointerManager::getInstance().setVisible(false);

    _windowConnector = new ConnectorWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    _windowConnector->getWidget()->setVisible(false);

    MyGUI::ResourceManager::getInstance().load("ButtonImage.resource");
    MyGUI::LayoutManager::getInstance().loadLayout("menu.layout");
    MyGUI::LayoutManager::getInstance().loadLayout("edit.layout");
    MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());

    _windowConnector = new ConnectorWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    _windowConnector->getWidget()->setVisible(false);
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("cancelButton"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("okButton"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_layer"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_layer_s"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_initial"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_activity"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_merge"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_decision"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_join"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fork"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_final"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_seq"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_alt"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_fragment_loop"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_dependency"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_dependency_straight"));
    //_buttons.push_back(mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Association", "Association", 120));
    //_buttons.push_back(mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Generalization", "Generalization", 120));
    //_buttons.push_back(mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Aggregation", "Aggregation", 120));
    //_buttons.push_back(mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "Remove_All", "Remove All", 120));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_export"));
    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_import"));

    _buttons.push_back(MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("button_menu"));

    for (int i=0; i < (int)_buttons.size(); i++)
    {
        _buttons[i]->eventMouseButtonClick += MyGUI::newDelegate(this, &Gui::notifyMyGUImenu);
    }
    _buttons.back()->setPosition(mCamera->getViewport()->getActualWidth()-60,10);

    MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
    editWidget->setVisible(edit_visible);

    MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
    widget->setVisible(tab_visible);
    widget->setPosition(mCamera->getViewport()->getActualWidth()-290,30);
    // set callback

    mCamera->setPosition(Ogre::Vector3(0,200,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
}

void Gui::editText()
{}

void Gui::initContent()
{}

ActivityWindow* Gui::getActivityWindow()
{
    return _activityWindow;
}

void Gui::closeActivityWindow()
{
    // TODO: destroy mygui widget
    _activityWindow->getWidget()->setVisible(false);
    MyGUI::PointerManager::getInstance().setVisible(false);
}

void Gui::releaseContent()
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

    MyGUI::Gui::getInstance().destroyWidget(_activityWindow->getWidget());
    MyGUI::Gui::getInstance().destroyWidget(_windowConnector->getWidget());

    DataManager::getInstance()->resetFactories();
}

MyGUI::WindowPtr Gui::getWidget()
{
    return widget;
}

void Gui::notifyMouseClick(int _x, int _y,  OIS::MouseButtonID id)
{
    DEF_BEGIN;
    GuiManager* guiM = GuiManager::getInstance();
    guiM->setPosition(Main::sMSceneMgr->getRootSceneNode()->convertLocalToWorldPosition(Ogre::Vector3(_x, _y, 0)));
    std::cout << "Click " << guiM->getPosition().x << ", " << guiM->getPosition().y << ", " << guiM->getPosition().z << std::endl;
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    DataManager* dataM = DataManager::getInstance();

    if (lay1 == NULL)
    {
        //lay1 = dataM->createLayer();
    }
    if (id == OIS::MB_Left)
    {
        std::pair<Element*, MetamodelElement*> element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(_x, _y));

        if (element.first != NULL)
        {
            guiM->setElement(element.first);
            if (element.first->selected)
            {
                UnselectItem(element.second->getName());
            }
            else
            {
                SelectItem(element.second->getName());
            }
        }
        else
        {
            guiM->setElement(NULL);
            std::cout << "Elem " << guiM->getElement() << std::endl;
        }

        if (element.first == NULL)
        {
            clearSelection();
        }
    }

    if (lastClickedButton == "button_initial")
    {
        dataM->createInitialNode(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_decision")
    {
        dataM->createDecision(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_fork")
    {
        dataM->createFork(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_join")
    {
        dataM->createJoin(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_merge")
    {
        dataM->createMerge(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_final")
    {
        dataM->createFinalNode(lay1, new Ogre::Vector2(_x, _y));
        lastClickedButton = "";
    }
    else if (lastClickedButton == "button_fragment_seq")
    {
    	typeOfElement = "seq";
    	MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
    	edit_visible = true;
    	editWidget->setVisible(edit_visible);
    	Ogre::Vector2* point = new Ogre::Vector2(_x, _y);
    	width = ElementCollection::getInstance()->getDefaultWidthOfFragment(point);
    	height = ElementCollection::getInstance()->getDefaultHeightOfFragment(point);
    	elementVector = ElementCollection::getInstance()->getDefaultCenterOfFragment(point);
    	stringstream ss;
    	ss << height;
    	inputString = ss.str();
    	MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
    	textBoxWidget->setProperty("Widget_Caption", inputString);
    	editWidget->setProperty("Widget_Caption", "Set height");
    	fragmentPos++;
    }
    else if (lastClickedButton == "button_fragment_alt")
    {
        typeOfElement = "alt";
        MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        edit_visible = true;
        editWidget->setVisible(edit_visible);
        Ogre::Vector2* point = new Ogre::Vector2(_x, _y);
        width = ElementCollection::getInstance()->getDefaultWidthOfFragment(point);
        height = ElementCollection::getInstance()->getDefaultHeightOfFragment(point);
        elementVector = ElementCollection::getInstance()->getDefaultCenterOfFragment(point);
        stringstream ss;
        ss << height;
        inputString = ss.str();
        MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        textBoxWidget->setProperty("Widget_Caption", inputString);
        editWidget->setProperty("Widget_Caption", "Set height");
        fragmentPos++;
    }
    else if (lastClickedButton == "button_fragment_loop")
    {
        typeOfElement= "loop";
        MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        edit_visible = true;
        editWidget->setVisible(edit_visible);
        Ogre::Vector2* point = new Ogre::Vector2(_x, _y);
        width = ElementCollection::getInstance()->getDefaultWidthOfFragment(point);
        height = ElementCollection::getInstance()->getDefaultHeightOfFragment(point);
        elementVector = ElementCollection::getInstance()->getDefaultCenterOfFragment(point);
        stringstream ss;
        ss << height;
        inputString = ss.str();
        MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        textBoxWidget->setProperty("Widget_Caption", inputString);
        editWidget->setProperty("Widget_Caption", "Set height");
        fragmentPos++;
    }
    else if (lastClickedButton == "button_activity")
    {
        typeOfElement = "activity";
        MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
        edit_visible = true;
        editWidget->setVisible(edit_visible);
        elementVector = new Ogre::Vector2(_x, _y);
        activity++;
        std::ostringstream inputStringStream;
        inputStringStream << "Activity " << activity;
        inputString = inputStringStream.str();
        MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");
        textBoxWidget->setProperty("Wiget_Caption", inputString);
    }
    else if (lastClickedButton == "button_dependency")
    {
        if(selectedElements.size() == 2 && selectedElements[0].first != NULL && selectedElements[1].first != NULL)
        {

            SetFlowStraight(false);
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
            lastClickedButton = "";
        }
    }

    else if (lastClickedButton == "button_dependency_straight")
    {
        if(selectedElements.size() == 2 && selectedElements[0].first != NULL && selectedElements[1].first != NULL)
        {
            SetFlowStraight(true);
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

    else if (lastClickedButton == "button_association")
    {
        if(rememberSelectedElement(_x, _y) == 2)
        {
            //DataManager::getInstance()->createAssociation(selectedElements[0], selectedElements[1]);
            clearSelection();
            lastClickedButton = "";
        }
    }
    else if (lastClickedButton == "button_generalization")
    {
        if(rememberSelectedElement(_x, _y) == 2)
        {
            //DataManager::getInstance()->createGeneralisation(selectedElements[0], selectedElements[1]);
            clearSelection();
            lastClickedButton = "";
        }
    }
    else if (lastClickedButton == "button_aggregation")
    {
        if(rememberSelectedElement(_x, _y) == 2)
        {
            //DataManager::getInstance()->createAggregation(selectedElements[0], selectedElements[1]);
            clearSelection();
            lastClickedButton = "";
        }
    }

    DrawManager::getInstance()->drawAll();
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    DEF_END;
}
void Gui::notifyMyGUImenu(MyGUI::Widget * _sender)
{
    DEF_BEGIN;
    DataManager* dataM = DataManager::getInstance();
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
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
        printSelected();
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

    MyGUI::Widget* widget = MyGUI::Gui::getInstance().findWidgetT("tab");
    MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");

    editWidget->setVisible(edit_visible);
    widget->setVisible(tab_visible);
    DrawManager::getInstance()->drawAll();
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    DEF_END;
}


void Gui::notifyMouseButtonClick(MyGUI::Widget * _sender,  OIS::MouseButtonID id)
{
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
}



void Gui::notifyKeyboardButton(OIS::KeyCode key)
{
    DEF_BEGIN;

    DataManager* dataM = DataManager::getInstance();

    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();

    MyGUI::Widget* textBoxWidget = MyGUI::Gui::getInstance().findWidget<MyGUI::Edit>("editBox");

    if (typeOfElement.compare("edge") == 0 || typeOfElement.compare("activity") == 0 || typeOfElement.compare("loop") == 0 || typeOfElement.compare("alt") == 0 || typeOfElement.compare("seq")==0)
    {
        std::cout<<key<<std::endl;
        if (key == OIS::KC_BACK)
        {
            if(inputString.length()>0)
                inputString = inputString.substr(0, inputString.length()-1);
            textBoxWidget->setProperty("Wiget_Caption", inputString);
        }
        else if (key == OIS::KC_ESCAPE && typeOfElement.compare("alt") == 0)
        {
            dataM->createAlt(lay1, elementVector, fragmentVector);
            typeOfElement = "";
            fragmentPos = 0;
            fragmentVector.clear();
        }
        else if (key == OIS::KC_RETURN || key == OIS::KC_NUMPADENTER)
        {
            edit_visible = false;
            if(typeOfElement.compare("acitivity") == 0)
            {
                dataM->createActivity(lay1, inputString, elementVector);
                typeOfElement = "";
            }
            else if (typeOfElement.compare("decision") == 0)
            {
                DataManager::getInstance()->createFlow(selectedElements[0].second->getName(), selectedElements[1].second->getName(), inputString);
                decision = !decision;
                typeOfElement = "";
            }
            else if(typeOfElement.compare("loop")==0)
            {
                if (fragmentPos == 1)
                {
                    fragmentVector[1] = inputString;
                    int width = ElementCollection::getInstance()->getDefaultWidthOfFragment(elementVector);
                 	int height = ElementCollection::getInstance()->getDefaultHeightOfFragment(elementVector);
                 	Ogre::Vector2* point= ElementCollection::getInstance()->getDefaultCenterOfFragment(elementVector);
                    dataM->createLoop(lay1,point,fragmentVector[0],fragmentVector[1],width,height);
                    fragmentPos = 0;
                    fragmentVector.clear();
                    typeOfElement = "";
                }
                else
                {
                    fragmentVector[0] = inputString;
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
            lastClickedButton = "";
            MyGUI::Widget* editWidget = MyGUI::Gui::getInstance().findWidgetT("edit_window");
            editWidget->setVisible(edit_visible);
            inputString = "";
        }
        else
        {
            std::ostringstream inputStringStream;
            inputStringStream << inputString;
            inputStringStream << returnAsString(key);
            inputStringStream << "\0";
            inputString = inputStringStream.str();
            textBoxWidget->setProperty("Wiget_Caption", inputString);
        }
    }

    std::cout<<lastClickedButton<<std::endl;
    if (lastClickedButton == "button_layer_s")
    {
        if (key == OIS::KC_R) //Up
            DrawManager::getInstance()->IncrementLayer();
        else if (key == OIS::KC_F )
            DrawManager::getInstance()->DecrementLayer();
        lay1 = DrawManager::getInstance()->getSelectedLayer();
        DrawManager::getInstance()->DrawSelectedLayers();
    }

    DrawManager::getInstance()->drawAll();
    mCamera->setPosition(Ogre::Vector3(0,0,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
}

MyGUI::Widget* Gui::getButtonWithState()
{
    return MyGUI::InputManager::getInstance().getMouseFocusWidget();
}

Gui* Gui::getWindowClass()
{
    return this;
}

ConnectorWindow* Gui::getWindowConnector()
{
    return _windowConnector;
}

void Gui::closeClassWindow()
{}

void Gui::closeConnectorWindow()
{}

int Gui::rememberSelectedElement(int _x, int _y)
{
    std::pair<Element*, MetamodelElement*> element = ElementCollection::getInstance()->searchCloseElement(new Ogre::Vector2(_x, _y));

    if(element.first != NULL && element.first->selected)
    {
        SelectItem(element.second->getName());
    }
    else
    {
        UnselectItem(element.second->getName());
    }
    return selectedElements.size();
}

bool Gui::selected(const std::string& A_name)
{
    for (auto i: selectedElements)
        if(i.second->getName() == A_name)
        {
            return true;
        }

    return false;
}

int Gui::getIndex(const std::string& A_name)
{
    for(int i = 0; i < (int) selectedElements.size(); ++i)
    {
        if(selectedElements[i].second->getName() == A_name)
        {
            return i;
        }
    }
    return -1;
}

void Gui::clearSelection()
{
    for(auto i : selectedElements)
    {
        i.first->selected = false;
        DrawManager::getInstance()->unselect(i.second->getName());
    }
    selectedElements.clear();
}

//TODO remove ASAP
void Gui::printSelected()
{
    DEF_BEGIN;
    for(int i = 0; i < (int) selectedElements.size(); ++i)
    {
        std::cout << "ELEM " << i << ": " << selectedElements[i].second->getName() << std::endl;
    }
}

void Gui::DeleteSelecedItems()
{
    for(int i = 0; i < (int) selectedElements.size(); ++i)
    {
        ElementCollection::getInstance()->removeElement(selectedElements[i].second->getName());
    }
    selectedElements.clear();
}
void Gui::SelectItem(const std::string& A_name)
{
    std::pair<Element*, MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);

    if (!elem.first->selected)
    {
        elem.first->selected = true;
        selectedElements.push_back(elem);
        DrawManager::getInstance()->select(A_name);
    }
}
void Gui::UnselectItem(const std::string& A_name)
{
    std::pair<Element*, MetamodelElement*> elem = ElementCollection::getInstance()->findElement(A_name);

    if (elem.first->selected)
    {
        elem.first->selected = false;
        selectedElements.erase(selectedElements.begin() + getIndex(elem.second->getName()));
        DrawManager::getInstance()->unselect(A_name);
    }
}
void Gui::SetFlowStraight(bool str)
{
    flowStraight = str;
}

bool Gui::GetFlowStraight(void)
{
    return flowStraight;
}
std::string Gui::returnAsString(OIS::KeyCode key)
{
                           std::string str = "";
                           switch (key)
                           {
                           case OIS::KC_1           :
                               str = "1";
                               break;
                           case OIS::KC_2           :
                               str = "2";
                               break;
                           case OIS::KC_3           :
                               str = "3";
                               break;
                           case OIS::KC_4           :
                               str = "4";
                               break;
                           case OIS::KC_5           :
                               str = "5";
                               break;
                           case OIS::KC_6           :
                               str = "6";
                               break;
                           case OIS::KC_7           :
                               str = "7";
                               break;
                           case OIS::KC_8           :
                               str = "8";
                               break;
                           case OIS::KC_9           :
                               str = "9";
                               break;
                           case OIS::KC_0           :
                               str = "0";
                               break;
                           case OIS::KC_MINUS       :
                               str = "-";
                               break;    // - on main keyboard
                           case OIS::KC_EQUALS      :
                               str = "=";
                               break;
                           case OIS::KC_BACK        :
                               str = "\\";
                               break;    // backspace
                           case OIS::KC_Q           :
                               str = "q";
                               break;
                           case OIS::KC_W           :
                               str = "w";
                               break;
                           case OIS::KC_E           :
                               str = "e";
                               break;
                           case OIS::KC_R           :
                               str = "r";
                               break;
                           case OIS::KC_T           :
                               str = "t";
                               break;
                           case OIS::KC_Y           :
                               str = "y";
                               break;
                           case OIS::KC_U           :
                               str = "u";
                               break;
                           case OIS::KC_I           :
                               str = "i";
                               break;
                           case OIS::KC_O           :
                               str = "o";
                               break;
                           case OIS::KC_P           :
                               str = "p";
                               break;
                           case OIS::KC_LBRACKET    :
                               str = "(";
                               break;
                           case OIS::KC_RBRACKET    :
                               str = ")";
                               break;
                           case OIS::KC_A           :
                               str = "a";
                               break;
                           case OIS::KC_S           :
                               str = "s";
                               break;
                           case OIS::KC_D           :
                               str = "d";
                               break;
                           case OIS::KC_F           :
                               str = "f";
                               break;
                           case OIS::KC_G           :
                               str = "g";
                               break;
                           case OIS::KC_H           :
                               str = "h";
                               break;
                           case OIS::KC_J           :
                               str = "j";
                               break;
                           case OIS::KC_K           :
                               str = "k";
                               break;
                           case OIS::KC_L           :
                               str = "l";
                               break;
                           case OIS::KC_Z           :
                               str = "z";
                               break;
                           case OIS::KC_X           :
                               str = "x";
                               break;
                           case OIS::KC_C           :
                               str = "c";
                               break;
                           case OIS::KC_V           :
                               str = "v";
                               break;
                           case OIS::KC_B           :
                               str = "b";
                               break;
                           case OIS::KC_N           :
                               str = "n";
                               break;
                           case OIS::KC_M           :
                               str = "m";
                               break;
                           case OIS::KC_COMMA       :
                               str = ",";
                               break;
                           case OIS::KC_PERIOD      :
                               str = ".";
                               break;    // . on main keyboard
                           case OIS::KC_SLASH       :
                               str = "/";
                               break;    // / on main keyboard
                           case OIS::KC_MULTIPLY    :
                               str = "*";
                               break;    // * on numeric keypad
                           case OIS::KC_SPACE       :
                               str = " ";
                               break;
                           default:
                               str = "";
                           }
                           return str;
                       }
}


