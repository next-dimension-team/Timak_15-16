/*
 * FillClassDetailsState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef FILLCLASSDETAILSSTATE_H_
#define FILLCLASSDETAILSSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../ApplicationState.h"

class FillClassDetailsState: public ApplicationState {
	public:
		FillClassDetailsState(ApplicationState* parentState);
		virtual ~FillClassDetailsState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* FILLCLASSDETAILSSTATE_H_ */
