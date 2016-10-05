/*
 * InsertConnectorState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCONNECTORSTATE_H_
#define INSERTCONNECTORSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"

class InsertConnectorState: public ApplicationState {
	public:
		InsertConnectorState(ApplicationState* parentState);
		virtual ~InsertConnectorState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* INSERTCONNECTORSTATE_H_ */
