/*
 * ActivityDiagramState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef ACTIVITYDIAGRAMSTATE_H_
#define ACTIVITYDIAGRAMSTATE_H_

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "ApplicationState.h"
#include "Message.h"

class ActivityDiagramState: public ApplicationState {
	public:
		ActivityDiagramState(ApplicationState* parentState);
		virtual ~ActivityDiagramState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
		virtual void processMessage(Message message);
	protected:
		virtual void initInternalStates();
};

#endif /* ACTIVITYDIAGRAMSTATE_H_ */
