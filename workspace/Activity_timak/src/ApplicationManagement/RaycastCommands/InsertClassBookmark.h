/*
 * InsertClassBookmark.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTCLASSBOOKMARK_H_
#define INSERTCLASSBOOKMARK_H_

#include "RaycastCommand.h"

class InsertClassBookmark: public RaycastCommand {
	public:
		InsertClassBookmark();
		virtual ~InsertClassBookmark();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* INSERTCLASSBOOKMARK_H_ */
