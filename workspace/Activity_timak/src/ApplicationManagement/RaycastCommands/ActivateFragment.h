/*
 * ActivateFragment.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef ACTIVATEFRAGMENT_H_
#define ACTIVATEFRAGMENT_H_

#include "RaycastCommand.h"

class ActivateFragment: public RaycastCommand {
	public:
		ActivateFragment();
		virtual ~ActivateFragment();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* ACTIVATEFRAGMENT_H_ */
