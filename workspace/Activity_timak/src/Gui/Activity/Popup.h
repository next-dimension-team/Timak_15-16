/*
 * Popup.h
 *
 *  Created on: 16.12.2013
 *      Author: Schade
 */

#ifndef POPUP_H_
#define POPUP_H_

namespace OIS {
	class MouseState;
}

#include "MyGUI_PopupMenu.h"
#include "OgreVector2.h"


class Popup {
	public:
		Popup();
		virtual ~Popup();

		static void displayPopup(int x, int y);

		static OIS::MouseState getMouseState();

		static bool isActive();

	private:
		static MyGUI::PopupMenu* widget;

		static void lostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new);

		static void notifyMouseButtonClick(MyGUI::Widget* _sender);

		static int x, y;
};

#endif /* POPUP_H_ */
