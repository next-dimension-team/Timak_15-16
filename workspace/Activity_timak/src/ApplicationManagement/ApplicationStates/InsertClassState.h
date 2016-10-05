/*
 * InsertClassState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCLASSSTATE_H_
#define INSERTCLASSSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"

class InsertClassState: public ApplicationState {
	public:
		InsertClassState(ApplicationState* parentState);
		virtual ~InsertClassState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* INSERTCLASSSTATE_H_ */
