/*
 * SelectClassPositionState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCLASSPOSITIONSTATE_H_
#define SELECTCLASSPOSITIONSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectClassPositionState: public ApplicationState {
	public:
		SelectClassPositionState(ApplicationState* parentState);
		virtual ~SelectClassPositionState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCLASSPOSITIONSTATE_H_ */
