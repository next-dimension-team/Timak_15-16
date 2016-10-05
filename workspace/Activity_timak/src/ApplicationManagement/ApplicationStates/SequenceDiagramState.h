/*
 * SequenceDiagramState.h
 *
 *  Created on: Nov 8, 2015
 *      Author: Matej
 */

#ifndef SRC_APPLICATIONMANAGEMENT_APPLICATIONSTATES_SEQUENCEDIAGRAMSTATE_H_
#define SRC_APPLICATIONMANAGEMENT_APPLICATIONSTATES_SEQUENCEDIAGRAMSTATE_H_

#include "ApplicationState.h"

class SequenceDiagramState: public ApplicationState {
public:
	SequenceDiagramState(ApplicationState* parentState);
	virtual ~SequenceDiagramState();
	virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void setNextState();
		virtual void processMessage(Message message);
	protected:
		virtual void initInternalStates();
};

#endif /* SRC_APPLICATIONMANAGEMENT_APPLICATIONSTATES_SEQUENCEDIAGRAMSTATE_H_ */
