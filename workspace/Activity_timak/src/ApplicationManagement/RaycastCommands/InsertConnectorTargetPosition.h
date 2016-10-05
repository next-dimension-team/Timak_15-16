/*
 * InsertConnectorTargetPosition.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCONNECTORTARGETPOSITION_H_
#define INSERTCONNECTORTARGETPOSITION_H_

#include "RaycastCommand.h"

class Class;

class InsertConnectorTargetPosition: public RaycastCommand {
	public:
		InsertConnectorTargetPosition();
		virtual ~InsertConnectorTargetPosition();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();

	private:
		Class* cla;
};

#endif /* INSERTCONNECTORTARGETPOSITION_H_ */
