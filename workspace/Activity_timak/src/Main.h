/*
 * Main.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "OgreFramework/OgreFramework.h"

class Main: public OgreFramework {
public:
	static Ogre::SceneManager* sMSceneMgr;

	Main(void);
	virtual ~Main(void);

protected:
	virtual void createScene(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
};

#endif /* MAIN_H_ */
