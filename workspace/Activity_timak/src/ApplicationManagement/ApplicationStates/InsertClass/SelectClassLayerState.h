/*
 * SelectClassLayerState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCLASSLAYERSTATE_H_
#define SELECTCLASSLAYERSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectClassLayerState: public ApplicationState {
	public:
		SelectClassLayerState(ApplicationState* parentState);
		virtual ~SelectClassLayerState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCLASSLAYERSTATE_H_ */
