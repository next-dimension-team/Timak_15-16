/*
 * ActivityWindow.h
 *
 *  Created on: 25.11.2013
 *      Author: Schade
 */

#ifndef ACTIVITYWINDOW_H_
#define ACTIVITYWINDOW_H_

namespace MyGUI
{
    class Gui;
    class Widget;
}

class Container;

#include <OgreVector2.h>
#include "MyGUI_Window.h"

#include <string>


class ActivityWindow
{
    public:
        ActivityWindow(double width, double height);

        void notifyMouseButtonClick(MyGUI::Widget* _sender);

        MyGUI::WindowPtr getWidget();
        void fillDefaultText();

        void setData(Container* container, Ogre::Vector2* position);

    private:
        void parse();

        MyGUI::WindowPtr widget;
        Ogre::Vector2* position;
        Container* container;

        std::string activityName;
};

#endif /* ACTIVITYWINDOW_H_ */
