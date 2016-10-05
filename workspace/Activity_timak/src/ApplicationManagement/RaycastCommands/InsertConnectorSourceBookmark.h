/*
 * InsertConnectorSourceBookmark.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCONNECTORSOURCEBOOKMARK_H_
#define INSERTCONNECTORSOURCEBOOKMARK_H_

#include "RaycastCommand.h"

class InsertConnectorSourceBookmark: public RaycastCommand {
	public:
		InsertConnectorSourceBookmark();
		virtual ~InsertConnectorSourceBookmark();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* INSERTCONNECTORSOURCEBOOKMARK_H_ */
