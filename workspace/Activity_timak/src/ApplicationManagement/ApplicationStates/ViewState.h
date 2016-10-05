/*
 * ViewState.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef VIEWSTATE_H_
#define VIEWSTATE_H_

#include <OISKeyboard.h>

#include "ApplicationState.h"

class ViewState: public ApplicationState {
	public:
		ViewState(ApplicationState* parentState);
		virtual ~ViewState();
		virtual void init();
		virtual void processButton(OIS::KeyCode key);
	protected:
		virtual void initInternalStates();
};

#endif /* VIEWSTATE_H_ */
