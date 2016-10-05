/*
 * SelectDiagramState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef SELECTDIAGRAMSTATE_H_
#define SELECTDIAGRAMSTATE_H_

#include <OISKeyboard.h>

#include "ApplicationState.h"
#include "Message.h"

class SelectDiagramState: public ApplicationState {
	public:
		SelectDiagramState(ApplicationState* parentState);
		virtual ~SelectDiagramState();
		virtual void processButton(OIS::KeyCode key);
		virtual void processMessage(Message message);
};

#endif /* SELECTDIAGRAMSTATE_H_ */
