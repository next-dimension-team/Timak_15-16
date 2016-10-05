/*
 * MouseManager.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef MOUSEMANAGER_H_
#define MOUSEMANAGER_H_

#include <OISMouse.h>

class MouseManager : public OIS::MouseListener
{
	public:
		MouseManager();
		~MouseManager();

		static MouseManager* getInstance();

	private:
		static MouseManager* singletonObject;

		// OIS::MouseListener
		bool mouseMoved( const OIS::MouseEvent &arg );
		bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
};

#endif /* MOUSEMANAGER_H_ */
