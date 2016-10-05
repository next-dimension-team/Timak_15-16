/*
 * InsertConnectorTargetBookmark.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCONNECTORTARGETBOOKMARK_H_
#define INSERTCONNECTORTARGETBOOKMARK_H_

#include "RaycastCommand.h"

class InsertConnectorTargetBookmark: public RaycastCommand {
	public:
		InsertConnectorTargetBookmark();
		virtual ~InsertConnectorTargetBookmark();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* INSERTCONNECTORTARGETBOOKMARK_H_ */
