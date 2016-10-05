/*
 * InsertActivityState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTACTIVITYSTATE_H_
#define INSERTACTIVITYSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class InsertActivityState: public ApplicationState {
	public:
		InsertActivityState(ApplicationState* parentState);
		virtual ~InsertActivityState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* INSERTACTIVITYSTATE_H_ */
