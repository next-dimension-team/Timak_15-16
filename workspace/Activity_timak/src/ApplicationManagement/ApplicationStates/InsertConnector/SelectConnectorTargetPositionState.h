/*
 * SelectConnectorTargetPositionState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCONNECTORTARGETPOSITIONSTATE_H_
#define SELECTCONNECTORTARGETPOSITIONSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectConnectorTargetPositionState: public ApplicationState {
	public:
		SelectConnectorTargetPositionState(ApplicationState* parentState);
		virtual ~SelectConnectorTargetPositionState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCONNECTORTARGETPOSITIONSTATE_H_ */
