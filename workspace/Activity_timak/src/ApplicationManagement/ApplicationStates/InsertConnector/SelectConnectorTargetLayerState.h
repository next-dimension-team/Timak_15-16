/*
 * SelectConnectorTargetLayerState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCONNECTORTARGETLAYERSTATE_H_
#define SELECTCONNECTORTARGETLAYERSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectConnectorTargetLayerState: public ApplicationState {
	public:
		SelectConnectorTargetLayerState(ApplicationState* parentState);
		virtual ~SelectConnectorTargetLayerState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCONNECTORTARGETLAYERSTATE_H_ */
