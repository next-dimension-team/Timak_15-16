/*
 * RaycastCommand.cpp
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#include "RaycastCommand.h"

RaycastCommand::RaycastCommand()
{

}

RaycastCommand::~RaycastCommand()
{

}

bool RaycastCommand::conditionsAccepted() { return 0; }
bool RaycastCommand::check() { return 0; }
void RaycastCommand::action() {}
bool RaycastCommand::stop() { return 0; }
void RaycastCommand::postProcessAction() {}
