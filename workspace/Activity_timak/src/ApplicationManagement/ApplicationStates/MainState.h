/*
 * MainState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef MAINSTATE_H_
#define MAINSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"
#include "Message.h"

class MainState: public ApplicationState {
	public:
		MainState(ApplicationState* parentState);
		virtual ~MainState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void processMessage(Message message);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* MAINSTATE_H_ */
