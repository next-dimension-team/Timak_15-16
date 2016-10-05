/*
 * ApplicationState.h
 *
 *  Created on: 5.10.2013
 *      Author: Schade
 */

#ifndef APPLICATIONSTATE_H_
#define APPLICATIONSTATE_H_

#include <map>

#include "Message.h"

class Message;

#include <OISKeyboard.h>
#include <OISMouse.h>
#include <string>


class ApplicationState
{
	public:
		ApplicationState(ApplicationState* parentState);
		virtual ~ApplicationState();

		static ApplicationState* initializator(ApplicationState* state);

		virtual void init();
		virtual void processButton(OIS::KeyCode key);
		virtual void processClick(OIS::MouseEvent arg, OIS::MouseButtonID id);
		virtual void processMessage(Message message);
		virtual void setNextState();

		void setState(std::string stateName);

	protected:
		ApplicationState* parentState;
		ApplicationState* currentInternalState;
		std::map<std::string, ApplicationState*> internalStates;

		virtual void initInternalStates();
};

#endif /* APPLICATIONSTATE_H_ */
