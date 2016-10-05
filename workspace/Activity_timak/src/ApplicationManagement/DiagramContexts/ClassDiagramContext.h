/*
 * ClassDiagramContext.h
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#ifndef CLASSDIAGRAMCONTEXT_H_
#define CLASSDIAGRAMCONTEXT_H_

class ClassWindow;
class ConnectorWindow;

namespace MyGUI {
	class RenderWindow;
	class SceneManager;
}

#include "DiagramContext.h"
#include <OISKeyboard.h>	// prerequisity for SdkTrays!!
#include <OISMouse.h>		// prerequisity for SdkTrays!!
#include <SdkTrays.h>		// TODO: create adapter!!


class ClassDiagramContext: public DiagramContext {
	public:
		ClassDiagramContext();
		virtual ~ClassDiagramContext();

		virtual void activateGui();
		virtual void initContent();
		virtual void releaseContent();

		OgreBites::ButtonState getClassButtonState();
		OgreBites::ButtonState getConnectionButtonState();
		OgreBites::ButtonState getLayerButtonState();
		ClassWindow* getWindowClass();
		ConnectorWindow* getWindowConnector();
		void closeClassWindow();
		void closeConnectorWindow();

	private:
		OgreBites::Button* mButton_Class;			// Button: Class
		OgreBites::Button* mButton_Connection;		// Button: Connection
		OgreBites::Button* mButton_Layer;			// Button: Layer

		ClassWindow* windowClass;
		ConnectorWindow* windowConnector;
};

#endif /* CLASSDIAGRAMCONTEXT_H_ */
