/*
 * SequenceDiagramContext.h
 *
 *  Created on: Nov 8, 2015
 *      Author: Matej
 */

#ifndef SRC_APPLICATIONMANAGEMENT_DIAGRAMCONTEXTS_SEQUENCEDIAGRAMCONTEXT_H_
#define SRC_APPLICATIONMANAGEMENT_DIAGRAMCONTEXTS_SEQUENCEDIAGRAMCONTEXT_H_

#include "DiagramContext.h"

class ActivityWindow;

#include <OISKeyboard.h>	// prerequisity for SdkTrays!!
#include <OISMouse.h>		// prerequisity for SdkTrays!!
#include <SdkTrays.h>		// TODO: create adapter!!
#include <vector>

#include <vector>
#include <string>
#include <OgreVector2.h>
#include "MyGUI_Window.h"
#include "MyGUI_Button.h"
#include "../../Gui/ConnectorWindow.h"

namespace MyGUI
{
    class RenderWindow;
    class SceneManager;
    class Widget;
}


using MyGUI::Window;

class SequenceDiagramContext: public DiagramContext {
	public:
		SequenceDiagramContext();
		virtual ~SequenceDiagramContext();
		virtual void activateGui();
		virtual void initContent();
		virtual void releaseContent();
		void inicializeWidget(double A_width, double A_height);
		ActivityWindow* getActivityWindow();
		void closeActivityWindow();

		void notifyMyGUImenu(MyGUI::Widget * _sender);
		void notifyMouseButtonClick(MyGUI::Widget * _sender, OIS::MouseButtonID id);
		void notifyKeyboardButton(OIS::KeyCode key);

	private:
		 ConnectorWindow* _windowConnector;
		 std::string lastClickedButton;
		 bool edit_visible;
		 bool tab_visible;
		 std::vector<MyGUI::Button*> _buttons;
		 //Layer* lay1;

		 MyGUI::WindowPtr widget;
};

#endif /* SRC_APPLICATIONMANAGEMENT_DIAGRAMCONTEXTS_SEQUENCEDIAGRAMCONTEXT_H_ */

