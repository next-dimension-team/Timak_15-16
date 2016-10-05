/*
 * ConnectorWindow.cpp
 *
 *  Created on: 18.6.2013
 *      Author: Schade
 */

#include "ConnectorWindow.h"

#include "MyGUI.h"

#include "../ApplicationManagement/ApplicationStateManager.h"
#include "../ApplicationManagement/DataManager.h"
#include "../ApplicationManagement/GuiManager.h"
#include "../Core/Aggregation.h"
#include "../Core/Association.h"
#include "../Core/Generalisation.h"
#include "../Core/Stereotype.h"
#include "../DataStructure/Association.h"


ConnectorWindow::ConnectorWindow(double width, double height) {
	this->widget = GuiManager::getInstance()->getGui()->createWidget<MyGUI::Window>("ConnectorCreateResource", 0, 0, width, height, MyGUI::Align::Default, "Main", "StereotypeCreateWindow");

	this->widget->findWidget("ConnectorCreateButton")->eventMouseButtonClick += MyGUI::newDelegate(this, &ConnectorWindow::notifyMouseButtonClick);
}


void ConnectorWindow::notifyMouseButtonClick(MyGUI::Widget* _sender) {
	if (_sender->getName() == "ConnectorCreateButton") {
		parse();

		Stereotype* s = 0;
		Element* createdElem = 0;
		if (this->widget->findWidget("ConnectorCreateComboBox")->castType<MyGUI::ComboBox>()->getCaption().compare("Association") == 0) {
			Association* connector = DataManager::getInstance()->createAssociation(this->source, this->target);
			s = DataManager::getInstance()->setNewStereotype(connector, this->stereotypeName);
			createdElem = connector;
		} else if (this->widget->findWidget("ConnectorCreateComboBox")->castType<MyGUI::ComboBox>()->getCaption().compare("Aggregation") == 0) {
			Aggregation* connector = DataManager::getInstance()->createAggregation(this->source, this->target);
			s = DataManager::getInstance()->setNewStereotype(connector, this->stereotypeName);
			createdElem = connector;
		} else if (this->widget->findWidget("ConnectorCreateComboBox")->castType<MyGUI::ComboBox>()->getCaption().compare("Generalisation") == 0) {
			Generalisation* connector = DataManager::getInstance()->createGeneralisation(this->source, this->target);
			createdElem = connector;
		}

		// TODO: draw?
		/*createdElem->draw();
		if (s != 0)
			s->draw();*/
		// FIXME: static_cast<Metamodel::Association*>(createdElem->getData())->getStereotype()->getWrapper()->draw();

		ApplicationStateManager::getInstance()->setNextState();
	}
}

MyGUI::WindowPtr ConnectorWindow::getWidget() {
	return this->widget;
}

void ConnectorWindow::fillDefaultText() {
	this->stereotypeName = "";

	this->widget->findWidget("ConnectorCreateEditBox")->castType<MyGUI::EditBox>()->setCaption(this->stereotypeName);
	this->widget->findWidget("ConnectorCreateComboBox")->castType<MyGUI::EditBox>()->setCaption("Association");
}

void ConnectorWindow::setSourceData(Class* source) {
	this->source = source;
}

void ConnectorWindow::setTargetData(Class* target) {
	this->target = target;
}

void ConnectorWindow::parse() {
	this->stereotypeName = this->widget->findWidget("ConnectorCreateEditBox")->castType<MyGUI::EditBox>()->getCaption();
}


