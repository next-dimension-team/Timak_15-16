/*
 * ConnectorWindow.h
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#ifndef CONNECTORWINDOW_H_
#define CONNECTORWINDOW_H_

namespace MyGUI
{
class Gui;
class Widget;
}

class Class;

#include "MyGUI_Window.h"

#include <string>


class ConnectorWindow
{
public:
    ConnectorWindow(double width, double height);

    void notifyMouseButtonClick(MyGUI::Widget* _sender);

    MyGUI::WindowPtr getWidget();
    void fillDefaultText();

    void setSourceData(Class* source);
    void setTargetData(Class* target);

private:
    void parse();

    MyGUI::WindowPtr widget;
    Class* source;
    Class* target;

    std::string stereotypeName;
};

#endif /* CONNECTORWINDOW_H_ */
