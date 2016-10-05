/*
 * ApplicationStateManager.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef APPLICATIONSTATEMANAGER_H_
#define APPLICATIONSTATEMANAGER_H_

class ApplicationState;
class DiagramContext;
class Message;

#include <OISKeyboard.h>
#include <OISMouse.h>


class ApplicationStateManager
{
	public:
		static ApplicationStateManager* getInstance();

		void processPressedButton(OIS::KeyCode key);
		void processClickedMouse(OIS::MouseEvent arg, OIS::MouseButtonID id);
		bool isReadyToShutdown();
		void setReadyToShutdown(bool readyToShutdown);

		void setNextState();
		void sendMessageToState(Message message);

		void update(double deltaTime);

		DiagramContext* getDiagramContext();
		void setDiagramContext(DiagramContext* context);

	private:
		bool readyToShutdown;

		ApplicationStateManager();
		virtual ~ApplicationStateManager();

		static ApplicationStateManager* singletonObject;

		ApplicationState* mainState;

		DiagramContext* context;
};

#endif /* APPLICATIONSTATEMANAGER_H_ */
