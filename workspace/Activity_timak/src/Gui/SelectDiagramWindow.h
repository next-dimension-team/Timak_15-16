/*
 * SelectDiagramWindow.h
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#ifndef SELECTDIAGRAMWINDOW_H_
#define SELECTDIAGRAMWINDOW_H_

namespace MyGUI {
	class Widget;
}

#include <OgreVector2.h>
#include "MyGUI_Window.h"


class SelectDiagramWindow {
	public:
		SelectDiagramWindow(double width, double height);

		void notifyMouseButtonClick(MyGUI::Widget* _sender);

		MyGUI::WindowPtr getWidget();

	private:
		MyGUI::WindowPtr widget;
		Ogre::Vector2* position;
};

#endif /* SELECTDIAGRAMWINDOW_H_ */
