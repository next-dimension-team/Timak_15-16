/*
 * SelectConnectorSourcePositionState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCONNECTORSOURCEPOSITIONSTATE_H_
#define SELECTCONNECTORSOURCEPOSITIONSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectConnectorSourcePositionState: public ApplicationState {
	public:
		SelectConnectorSourcePositionState(ApplicationState* parentState);
		virtual ~SelectConnectorSourcePositionState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCONNECTORSOURCEPOSITIONSTATE_H_ */
