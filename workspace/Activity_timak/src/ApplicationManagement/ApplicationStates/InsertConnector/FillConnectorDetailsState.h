/*
 * FillConnectorDetailsState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef FILLCONNECTORDETAILSSTATE_H_
#define FILLCONNECTORDETAILSSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class FillConnectorDetailsState: public ApplicationState {
	public:
		FillConnectorDetailsState(ApplicationState* parentState);
		virtual ~FillConnectorDetailsState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* FILLCONNECTORDETAILSSTATE_H_ */
