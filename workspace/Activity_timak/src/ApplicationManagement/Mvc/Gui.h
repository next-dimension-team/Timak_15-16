#ifndef GUI_H_
#define GUI_H_

#include "../DiagramContexts/DiagramContext.h"
#include <OISKeyboard.h>	// prerequisity for SdkTrays!!
#include <OISMouse.h>		// prerequisity for SdkTrays!!
#include <SdkTrays.h>		// TODO: create adapter!!
#include <vector>

#include <vector>
#include <string>
#include <OgreVector2.h>
#include "MyGUI_Window.h"
#include "MyGUI_Button.h"

class ActivityWindow;
class ConnectorWindow;
class Layer;
class Element;

namespace MyGUI
{
    class RenderWindow;
    class SceneManager;
    class Widget;
}

using MyGUI::Window;

namespace team4
{
	class MetamodelElement;
    class Gui : public DiagramContext
    {
        private:

			std::string lastClickedButton;

            ActivityWindow *_activityWindow;
            std::vector<std::pair<Element*, MetamodelElement*>> selectedElements;

            std::vector<MyGUI::Button*> _buttons;
            MyGUI::Button* button;
            bool tab_visible;

            std::vector<MyGUI::Edit*> _editBox;
            MyGUI::Edit* editBox;
            bool edit_visible;

            bool flowStraight;
            ConnectorWindow* _windowConnector;

            MyGUI::WindowPtr widget;
            MyGUI::WindowPtr getWidget();
            MyGUI::Gui * mGUI;
            Gui* getWindowClass();
            ConnectorWindow* getWindowConnector();
            void closeClassWindow();
            void closeConnectorWindow();
            bool selected(const std::string& A_name);
            int getIndex(const std::string& A_name);
            void printSelected();
            void clearSelection();

            void inicializeWidget(double A_width, double A_height);

        public:
            void notifyMyGUImenu(MyGUI::Widget * _sender);
            void notifyMouseButtonClick(MyGUI::Widget * _sender, OIS::MouseButtonID id);
            void notifyMouseClick(int _x, int _y,  OIS::MouseButtonID id);
            void notifyKeyboardButton(OIS::KeyCode key);
            std::string returnAsString(OIS::KeyCode key);
            MyGUI::Widget* getButtonWithState();
            int rememberSelectedElement(int _x, int _y);
            void DeleteSelecedItems();
            void SelectItem(const std::string& A_name);
            void UnselectItem(const std::string& A_name);
            void SetFlowStraight(bool str);
            bool GetFlowStraight(void);

            void refresh();
            Gui();
            ~Gui();

            virtual void activateGui();
            void editText();
            virtual void initContent();
            ActivityWindow* getActivityWindow();
            virtual void closeActivityWindow();
            virtual void releaseContent();

            Layer* lay1;

    };

}

#endif /* GUI_H_ */
