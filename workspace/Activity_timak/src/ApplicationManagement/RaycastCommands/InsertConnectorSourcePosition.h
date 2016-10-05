/*
 * InsertConnectorSourcePosition.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCONNECTORSOURCEPOSITION_H_
#define INSERTCONNECTORSOURCEPOSITION_H_

#include "RaycastCommand.h"

class Class;

class InsertConnectorSourcePosition: public RaycastCommand {
	public:
		InsertConnectorSourcePosition();
		virtual ~InsertConnectorSourcePosition();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();

	private:
		Class* cla;
};

#endif /* INSERTCONNECTORSOURCEPOSITION_H_ */
