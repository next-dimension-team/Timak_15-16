/*
 * Message.cpp
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#include "Message.h"

Message::Message(int enumValue)
{
	this->enumValue = enumValue;
}

Message::~Message() {}

int Message::getEnumValue() {
	return this->enumValue;
}
