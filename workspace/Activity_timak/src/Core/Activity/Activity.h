/*
 * Activity.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include <string>

#include "../Element.h"

class Activity: public Element
{
	friend class ActivityFactory;

	public:
		static const std::string ELEMENT_TYPE;
		virtual ~Activity();

	protected:
		Activity();
};


#endif /* ACTIVITY_H_ */
