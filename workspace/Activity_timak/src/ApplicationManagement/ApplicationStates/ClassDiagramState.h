/*
 * ClassDiagramState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef CLASSDIAGRAMSTATE_H_
#define CLASSDIAGRAMSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"

class ClassDiagramState: public ApplicationState {
	public:
		ClassDiagramState(ApplicationState* parentState);
		virtual ~ClassDiagramState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
	protected:
		virtual void initInternalStates();
};

#endif /* CLASSDIAGRAMSTATE_H_ */
