/*
 * InitialNode.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef INITIALNODE_CORE_H_
#define INITIALNODE_CORE_H_

#include <string>

#include "../Element.h"


class InitialNode: public Element
{
	friend class InitialNodeFactory;

	public:
		static const std::string ELEMENT_TYPE;
		virtual ~InitialNode();


	protected:
		InitialNode();
};


#endif /* INITIALNODE_H_ */
