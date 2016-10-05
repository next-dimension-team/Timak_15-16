/*
 * RaycastCommand.h
 *
 *  Created on: 9.7.2013
 *      Author: Schade
 */

#ifndef RAYCASTCOMMAND_H_
#define RAYCASTCOMMAND_H_

class RaycastCommand
{
	public:
		RaycastCommand();
		virtual ~RaycastCommand();

		bool virtual conditionsAccepted();
		bool virtual check();
		void virtual action();
		bool virtual stop();
		void virtual postProcessAction();
};

#endif /* RAYCASTCOMMAND_H_ */
