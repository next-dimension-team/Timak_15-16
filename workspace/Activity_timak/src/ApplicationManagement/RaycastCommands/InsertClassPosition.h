/*
 * InsertClassPosition.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCLASSPOSITION_H_
#define INSERTCLASSPOSITION_H_

#include "RaycastCommand.h"

class InsertClassPosition: public RaycastCommand {
	public:
		InsertClassPosition();
		virtual ~InsertClassPosition();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* INSERTCLASSPOSITION_H_ */
