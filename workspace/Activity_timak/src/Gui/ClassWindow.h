/*
 * ClassWindow.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef CLASSWINDOW_H_
#define CLASSWINDOW_H_

namespace MyGUI {
	class Widget;
}

class Layer;

#include <vector>
#include <string>
#include <OgreVector2.h>
#include "MyGUI_Window.h"


class ClassWindow {
	public:
		ClassWindow(double width, double height);

		void notifyMouseButtonClick(MyGUI::Widget* _sender);
		void notifyWindowClose(MyGUI::Window* _sender, const std::string& _name);

		MyGUI::WindowPtr getWidget();
		void fillDefaultText();

		void setData(Layer* layer, Ogre::Vector2* position);

	private:
		void parse();

		MyGUI::WindowPtr widget;
		Ogre::Vector2* position;
		Layer* layer;

		std::string className;
		std::vector<std::string> attributes;
		std::vector<std::string> methods;
};

#endif /* CLASSWINDOW_H_ */
