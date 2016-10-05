/*
 * SelectConnectorSourceLayerState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTCONNECTORSOURCELAYERSTATE_H_
#define SELECTCONNECTORSOURCELAYERSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class SelectConnectorSourceLayerState: public ApplicationState {
	public:
		SelectConnectorSourceLayerState(ApplicationState* parentState);
		virtual ~SelectConnectorSourceLayerState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* SELECTCONNECTORSOURCELAYERSTATE_H_ */
