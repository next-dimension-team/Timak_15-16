/*
 * FinalNode.h
 *
 *  Created on: 13.10.2013
 *      Author: Schade
 */

#ifndef FINALNODE_CORE_H_
#define FINALNODE_CORE_H_

#include "../Element.h"

class FinalNode: public Element
{
	friend class FinalNodeFactory;

	public:
		static const std::string ELEMENT_TYPE;
		virtual ~FinalNode();

	protected:
		FinalNode();
};


#endif /* FINALNODE_H_ */
