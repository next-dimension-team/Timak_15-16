/*
 * ActivityDiagramContext.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "ActivityDiagramContext.h"

#include <OgreMaterialManager.h>

#include <OgrePrerequisites.h>
#include <OgreTextureManager.h>
#include <WIN32/OgreTimerImp.h>


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
#include "../../Main.h"
#include "../DataManager.h"
#include "../DrawManager.h"
#include "../ElementCollection.h"
#include "../GuiManager.h"


ActivityDiagramContext::ActivityDiagramContext() : DiagramContext()
{
    activityWindow = NULL;
}

ActivityDiagramContext::~ActivityDiagramContext()
{}

void ActivityDiagramContext::activateGui()
{
    Ogre::Camera* mCamera = GuiManager::getInstance()->getCameraManager()->getCamera();
    this->activityWindow = new ActivityWindow(mCamera->getViewport()->getActualWidth(), mCamera->getViewport()->getActualHeight());
    this->activityWindow->getWidget()->setVisible(false);

    mCamera->setPosition(Ogre::Vector3(0,200,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
}

// Complex demonstration model
void ActivityDiagramContext::initContent()
{
    DataManager* dataM = DataManager::getInstance();

   /* Layer* lay1 = dataM->createLayer();
    InitialNode* in1 = dataM->createInitialNode(lay1, new Ogre::Vector2(-180, 0));
    FinalNode* fn1 = dataM->createFinalNode(lay1, new Ogre::Vector2(40, -100));
    Merge* dec1_1 = dataM->createMerge(lay1, new Ogre::Vector2(-150, -20));
    Decision* dec1_2 = dataM->createDecision(lay1, new Ogre::Vector2(-150, 0));
    Fork* dec1_3 = dataM->createFork(lay1, new Ogre::Vector2(-150, 20));
    Join* dec1_4 = dataM->createJoin(lay1, new Ogre::Vector2(-70, -20));

    Activity* act1_1 = dataM->createActivity(lay1, "No state change", new Ogre::Vector2(-100, -100));
    Activity* act1_2 = dataM->createActivity(lay1, "Mem. read request", new Ogre::Vector2(-110, -20));

    Fragment* fr1_1 = dataM->createFragment(lay1, new Ogre::Vector2(30, 0), "Exclusive copy", "<<ALT>>");
    Activity* act1_3 = dataM->createActivity(fr1_1, "Mem access stored", new Ogre::Vector2(-40, 20));
    Activity* act1_4 = dataM->createActivity(fr1_1, "Put copy on bus", new Ogre::Vector2(30, 20));
    Activity* act1_5 = dataM->createActivity(fr1_1, "Set state to S", new Ogre::Vector2(30, -20));

    dataM->createFlow(act1_3, act1_4);
    dataM->createFlow(act1_4, act1_5);
    Fragment* fr1_2 = dataM->createFragment(lay1, new Ogre::Vector2(30, 0), "Modified copy", "<<ALT>>", fr1_1);
    Activity* act1_6 = dataM->createActivity(fr1_2, "Access aborted", new Ogre::Vector2(-40, 20));
    Activity* act1_7 = dataM->createActivity(fr1_2, "Copy on bus", new Ogre::Vector2(-40, -20));
    Activity* act1_8 = dataM->createActivity(fr1_2, "Copy to main mem", new Ogre::Vector2(20, -20));
    Activity* act1_9 = dataM->createActivity(fr1_2, "States set to 8", new Ogre::Vector2(20, 20));

    dataM->createFlow(act1_6, act1_7);
    dataM->createFlow(act1_7, act1_8);
    dataM->createFlow(act1_8, act1_9);

    dataM->createFlow(in1, dec1_2);
    dataM->createFlow(dec1_2, dec1_1);
    dataM->createFlow(dec1_2, dec1_3);

    dataM->createFlow(dec1_1, act1_1);
    dataM->createFlow(dec1_1, act1_2);

    dataM->createFlow(act1_1, fn1);
    dataM->createFlow(act1_2, dec1_4);

    dataM->createFlow(dec1_4, fr1_1);
    dataM->createFlow(fr1_1, fn1);

    Layer* lay2 = dataM->createLayer();
    FinalNode* fn2 = dataM->createFinalNode(lay2, new Ogre::Vector2(160, 0));
    Decision* dec2_1 = dataM->createDecision(lay2, new Ogre::Vector2(-100, 0));

    Fragment* fr2_1 = dataM->createFragment(lay2, new Ogre::Vector2(0, 0), "Modified", "<<ALT>>");
    Activity* act2_1 = dataM->createActivity(fr2_1, "Update cache", new Ogre::Vector2(0, 0));
    Fragment* fr2_2 = dataM->createFragment(lay2, new Ogre::Vector2(0, 0), "Exclusive", "<<ALT>>", fr2_1);
    Activity* act2_2 = dataM->createActivity(fr2_2, "Update cache", new Ogre::Vector2(-30, 0));
    Activity* act2_3 = dataM->createActivity(fr2_2, "Change state E -> M", new Ogre::Vector2(30, 0));

    dataM->createFlow(act2_2, act2_3);
    Fragment* fr2_3 = dataM->createFragment(lay2, new Ogre::Vector2(0, 0), "Shared", "<<ALT>>", fr2_1);
    Activity* act2_4 = dataM->createActivity(fr2_3, "Broadcast invalid", new Ogre::Vector2(-40, -20));
    Activity* act2_5 = dataM->createActivity(fr2_3, "Cores state S -> I", new Ogre::Vector2(-40, 20));
    Activity* act2_6 = dataM->createActivity(fr2_3, "Update cache line", new Ogre::Vector2(40, 20));
    Activity* act2_7 = dataM->createActivity(fr2_3, "State S -> M", new Ogre::Vector2(40, -20));

    dataM->createFlow(act2_4, act2_5);
    dataM->createFlow(act2_5, act2_6);
    dataM->createFlow(act2_6, act2_7);

    dataM->createFlow(dec1_3, dec2_1);
    dataM->createFlow(dec2_1, fr2_1);

    dataM->createFlow(fr2_1, fn2);
    Layer* lay3 = dataM->createLayer();
    FinalNode* fn3 = dataM->createFinalNode(lay3, new Ogre::Vector2(80, -80));
    //Decision* dec3_1 = dataM->createDecision(lay3, new Ogre::Vector2(-100, -20));
    //Decision* dec3_2 = dataM->createDecision(lay3, new Ogre::Vector2(-80, 0));

    Activity* act3_1 = dataM->createActivity(lay3, "Broadcast RWITM", new Ogre::Vector2(-120, 0));
    Activity* act3_2 = dataM->createActivity(lay3, "State set to M", new Ogre::Vector2(0, -80));

    Fragment* fr3_1 = dataM->createFragment(lay3, new Ogre::Vector2(50, 0), "Modified copy", "<<ALT>>");
    Activity* act3_3 = dataM->createActivity(fr3_1, "RWITM blocked", new Ogre::Vector2(-40, 20));
    Activity* act3_4 = dataM->createActivity(fr3_1, "Write to main mem.", new Ogre::Vector2(-40, -20));
    Activity* act3_5 = dataM->createActivity(fr3_1, "State set to t", new Ogre::Vector2(40, -20));
    Activity* act3_6 = dataM->createActivity(fr3_1, "Core re-issues RWITM", new Ogre::Vector2(40, 20));

    dataM->createFlow(act3_3, act3_4);
    dataM->createFlow(act3_4, act3_5);
    dataM->createFlow(act3_5, act3_6);
    Fragment* fr3_2 = dataM->createFragment(lay3, new Ogre::Vector2(50, 0), "Exclusive/Shared copy", "<<ALT>>", fr3_1);
    Activity* act3_7 = dataM->createActivity(fr3_2, "Set state to t", new Ogre::Vector2(-40, 0));
    Activity* act3_8 = dataM->createActivity(fr3_2, "Sets state to M", new Ogre::Vector2(40, 0));

    dataM->createFlow(act3_7, act3_8);

    dataM->createFlow(dec1_3, act3_1);
    dataM->createFlow(act3_1, dec3_1);
    dataM->createFlow(dec3_1, dec3_2);
    dataM->createFlow(dec3_2, fr3_1);
    dataM->createFlow(dec3_1, act3_2);
    dataM->createFlow(act3_2, fn3);
    dataM->createFlow(fr3_1, act3_2);*/
}

// Test model
//void ActivityDiagramContext::initContent() {
//	DataManager* dataM = DataManager::getInstance();
//
//	for (int i = 0; i < 50; i++) {
//		Layer* lay1 = dataM->createLayer();
//			InitialNode* in1 = dataM->createInitialNode(lay1, new Ogre::Vector2(-120, 0));
//			Activity* act1 = dataM->createActivity(lay1, "Activity 1", new Ogre::Vector2(-70, 0));
//
//			Fragment* fr1 = dataM->createFragment(lay1, new Ogre::Vector2(50, 0), "a < 10", "<<ALT>>");
//				Activity* act2 = dataM->createActivity(fr1, "Activity A-1", new Ogre::Vector2(-30, 0));
//				Activity* act3 = dataM->createActivity(fr1, "Activity A-2", new Ogre::Vector2(30, 20));
//				Decision* dec1 = dataM->createDecision(fr1, new Ogre::Vector2(0, 0));
//				FinalNode* fn1 = dataM->createFinalNode(fr1, new Ogre::Vector2(30, -20));
//
//			Fragment* fr2 = dataM->createFragment(lay1, new Ogre::Vector2(50, 0), "a >= 10 && a < 20", "<<ALT>>", fr1);
//				Activity* act4 = dataM->createActivity(fr2, "Activity B-1", new Ogre::Vector2(-25, 0));
//				FinalNode* fn2 = dataM->createFinalNode(fr2, new Ogre::Vector2(25, 0));
//
//			Fragment* fr3 = dataM->createFragment(lay1, new Ogre::Vector2(50, 0), "a >= 20", "<<ALT>>", fr1);
//
//			dataM->createFlow(in1, act1);
//			dataM->createFlow(act1, fr1);
//
//			dataM->createFlow(act2, dec1);
//			dataM->createFlow(dec1, act3);
//			dataM->createFlow(dec1, fn1);
//
//			dataM->createFlow(act4, fn2);
//
//		Layer* lay2 = dataM->createLayer();
//			InitialNode* in2 = dataM->createInitialNode(lay2, new Ogre::Vector2(-140, 0));
//			Activity* act5 = dataM->createActivity(lay2, "Activity 5", new Ogre::Vector2(-100, 0));
//			Fragment* fr4 = dataM->createFragment(lay2, new Ogre::Vector2(10, 10), "", "<<PAR>>");
//				Decision* dec2 = dataM->createDecision(fr4, new Ogre::Vector2(-40, 0));
//				FinalNode* fn3 = dataM->createFinalNode(fr4, new Ogre::Vector2(50, 0));
//				Activity* act6 = dataM->createActivity(fr4, "Activity 6", new Ogre::Vector2(0, 0));
//				FinalNode* fn4 = dataM->createFinalNode(fr4, new Ogre::Vector2(-40, -30));
//			Fragment* fr4_1 = dataM->createFragment(lay2, new Ogre::Vector2(10, 10), "", "<<PAR>>", fr4);
//
//			dataM->createFlow(in2, act5);
//			dataM->createFlow(act5, fr4);
//
//			dataM->createFlow(dec2, fn4);
//			dataM->createFlow(dec2, act6);
//			dataM->createFlow(act6, fn3);
//
//		Layer* lay3 = dataM->createLayer();
//			Fragment* fr5 = dataM->createFragment(lay3, new Ogre::Vector2(50, 0), "", "<<PAR>>");
//				Activity* act7 = dataM->createActivity(fr5, "Activity 7", new Ogre::Vector2(-30, 0));
//				FinalNode* fn5 = dataM->createFinalNode(fr5, new Ogre::Vector2(40, 0));
//
//			dataM->createFlow(act7, fn5);
//	}
//}

void ActivityDiagramContext::releaseContent()
{
    Main::sMSceneMgr->clearScene();
    DrawManager::getInstance()->init(Main::sMSceneMgr);
    ElementCollection::getInstance()->removeAllElements();

    MyGUI::Gui::getInstance().destroyWidget(activityWindow->getWidget());

    DataManager::getInstance()->resetFactories();
}

ActivityWindow* ActivityDiagramContext::getActivityWindow()
{
    return this->activityWindow;
}

void ActivityDiagramContext::closeActivityWindow()
{
    // TODO: destroy mygui widget
    this->activityWindow->getWidget()->setVisible(false);
    MyGUI::PointerManager::getInstance().setVisible(false);
}
