/*
 * ClassDiagramContext.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "ClassDiagramContext.h"

#include <OgreMaterialManager.h>

#include <OgrePrerequisites.h>
#include <OgreTextureManager.h>
#include <WIN32/OgreTimerImp.h>

#include "../../Core/Class.h"
#include "../../Gui/ClassWindow.h"
#include "../../Gui/ConnectorWindow.h"
#include "../../Main.h"
#include "../DataManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../GuiManager.h"


ClassDiagramContext::ClassDiagramContext() : DiagramContext()
{}

ClassDiagramContext::~ClassDiagramContext()
{}

void ClassDiagramContext::activateGui()
{
    Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();

    OgreBites::SdkTrayManager* mTrayMgr = GuiManager::getInstance()->getTrayManager();
    mButton_Class = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Button_Class", "Class", 100);
    mButton_Connection = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Button_Connection", "Connection", 100);
    mButton_Layer = mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "Button_Layer", "Add Layer", 100);


    MyGUI::PointerManager::getInstance().setVisible(false);

    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    this->windowClass = new ClassWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    this->windowClass->getWidget()->setVisible(false);

    this->windowConnector = new ConnectorWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    this->windowConnector->getWidget()->setVisible(false);

    mCamera->setPosition(Ogre::Vector3(0,200,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
}


// Complex demonstration model #4 - transient/persistent data
void ClassDiagramContext::initContent()
{
    DataManager* dataM = DataManager::getInstance();
    Aggregation* agg;
    Association* ass;

    Layer* lay_transient = dataM->createLayer(); // Transient
    Class* session = dataM->createClass(lay_transient, "Session", new Ogre::Vector2(0, -40));
    Class* money = dataM->createClass(lay_transient, "Money", new Ogre::Vector2(-70, 120));
    Class* receipt = dataM->createClass(lay_transient, "Receipt", new Ogre::Vector2(90, -15));

    Layer* lay_biz = dataM->createLayer(); // Middle layer
    Class* atm = dataM->createClass(lay_biz, "ATM", new Ogre::Vector2(0, 0));
    Class* cashDispenser = dataM->createClass(lay_biz, "CashDispenser", new Ogre::Vector2(-90, 50));
    Class* envelopeAcceptor = dataM->createClass(lay_biz, "EnvelopeAcceptor", new Ogre::Vector2(0, 50));
    Class* networkToBank = dataM->createClass(lay_biz, "NetworkToBank", new Ogre::Vector2(90, 50));
    Class* customerConsole = dataM->createClass(lay_biz, "CustomerConsole", new Ogre::Vector2(-90, -10));
    Class* operatorPanel = dataM->createClass(lay_biz, "OperatorPanel", new Ogre::Vector2(90, -10));
    Class* cardReader = dataM->createClass(lay_biz, "CardReader", new Ogre::Vector2(-90, -40));
    Class* receiptPrinter = dataM->createClass(lay_biz, "ReceiptPrinter", new Ogre::Vector2(90, -40));

    Layer* lay_persistent = dataM->createLayer(); // Persistent
    Class* transaction = dataM->createClass(lay_persistent, "Transaction", new Ogre::Vector2(0, -40));
    Class* withdrawal = dataM->createClass(lay_persistent, "Withdrawal", new Ogre::Vector2(-60, -80));
    Class* deposit = dataM->createClass(lay_persistent, "Deposit", new Ogre::Vector2(-20, -80));
    Class* transfer = dataM->createClass(lay_persistent, "Transfer", new Ogre::Vector2(20, -80));
    Class* inquiry = dataM->createClass(lay_persistent, "Inquiry", new Ogre::Vector2(60, -80));
    Class* accountInformation = dataM->createClass(lay_persistent, "AccountInformation", new Ogre::Vector2(0, -120));
    Class* balances = dataM->createClass(lay_persistent, "Balances", new Ogre::Vector2(90, 120));
    Class* message = dataM->createClass(lay_persistent, "Message", new Ogre::Vector2(90, 50));
    Class* log = dataM->createClass(lay_persistent, "Log", new Ogre::Vector2(0, 50));
    Class* status = dataM->createClass(lay_persistent, "Status", new Ogre::Vector2(90, 20));
    Class* card = dataM->createClass(lay_persistent, "Card", new Ogre::Vector2(-90, -40));

    dataM->createGeneralisation(withdrawal, transaction);
    dataM->createGeneralisation(deposit, transaction);
    dataM->createGeneralisation(transfer, transaction);
    dataM->createGeneralisation(inquiry, transaction);

    agg = dataM->createAggregation(cashDispenser, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(envelopeAcceptor, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(networkToBank, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(log, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(customerConsole, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(operatorPanel, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(cardReader, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(receiptPrinter, atm);
    dataM->setNewStereotype(agg, "");
    agg = dataM->createAggregation(transaction, session);
    dataM->setNewStereotype(agg, "");

    ass = dataM->createAssociation(cashDispenser, log);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(envelopeAcceptor, log);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(networkToBank, log);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(session, atm);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(cardReader, card);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(session, card);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(transaction, card);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(withdrawal, accountInformation);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(deposit, accountInformation);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(transfer, accountInformation);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(inquiry, accountInformation);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(customerConsole, money);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(balances, money);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(message, balances);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(networkToBank, balances);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(networkToBank, message);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(networkToBank, status);
    dataM->setNewStereotype(ass, "");
    ass = dataM->createAssociation(receiptPrinter, receipt);
    dataM->setNewStereotype(ass, "");
}

void ClassDiagramContext::releaseContent()
{
    Main::sMSceneMgr->clearScene();
    DrawManager::getInstance()->init(Main::sMSceneMgr);
    ElementCollection::getInstance()->removeAllElements();

    OgreBites::SdkTrayManager* mTrayMgr = GuiManager::getInstance()->getTrayManager();
    mTrayMgr->destroyWidget(mButton_Class);
    mTrayMgr->destroyWidget(mButton_Connection);
    mTrayMgr->destroyWidget(mButton_Layer);
    MyGUI::Gui::getInstance().destroyWidget(windowClass->getWidget());
    MyGUI::Gui::getInstance().destroyWidget(windowConnector->getWidget());

    DataManager::getInstance()->resetFactories();
}

ClassWindow* ClassDiagramContext::getWindowClass()
{
    return this->windowClass;
}

ConnectorWindow* ClassDiagramContext::getWindowConnector()
{
    return this->windowConnector;
}

OgreBites::ButtonState ClassDiagramContext::getClassButtonState()
{
    return mButton_Class->getState();
}

OgreBites::ButtonState ClassDiagramContext::getConnectionButtonState()
{
    return mButton_Connection->getState();
}

OgreBites::ButtonState ClassDiagramContext::getLayerButtonState()
{
    return mButton_Layer->getState();
}

void ClassDiagramContext::closeClassWindow()
{
    // TODO: destroy mygui widget
    this->windowClass->getWidget()->setVisible(false);
    MyGUI::PointerManager::getInstance().setVisible(false);
}

void ClassDiagramContext::closeConnectorWindow()
{
    // TODO: destroy mygui widget
    this->windowConnector->getWidget()->setVisible(false);
    MyGUI::PointerManager::getInstance().setVisible(false);
}

