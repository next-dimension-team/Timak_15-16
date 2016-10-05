/*
 * KeyboardManager.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef KEYBOARDMANAGER_H_
#define KEYBOARDMANAGER_H_

#include <OISKeyboard.h>

class KeyboardManager : public OIS::KeyListener
{
	public:
		KeyboardManager();
		~KeyboardManager();

		static KeyboardManager* getInstance();

	private:
		static KeyboardManager* singletonObject;

		// OIS::KeyListener
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &arg );
};

#endif /* KEYBOARDMANAGER_H_ */
