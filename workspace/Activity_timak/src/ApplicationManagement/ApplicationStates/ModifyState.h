/*
 * ModifyState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef MODIFYSTATE_H_
#define MODIFYSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"
#include "Message.h"

class ModifyState: public ApplicationState {
	public:
		ModifyState(ApplicationState* parentState);
		virtual ~ModifyState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void processMessage(Message message);
	protected:
		virtual void initInternalStates();
};

#endif /* MODIFYSTATE_H_ */
