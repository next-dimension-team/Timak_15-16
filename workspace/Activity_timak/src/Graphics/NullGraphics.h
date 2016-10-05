/*
 * NullGraphics.h
 *
 *  Created on: 24.6.2013
 *      Author: Schade
 */

#ifndef NULLGRAPHICS_H_
#define NULLGRAPHICS_H_

#include "ElementGraphics.h"

class NullGraphics: public ElementGraphics
{
	public:
		static NullGraphics* getInstance();

		void draw(const std::string& A_name);

	private:
		NullGraphics();
		virtual ~NullGraphics();

		static NullGraphics* singletonObject;
};

#endif /* NULLGRAPHICS_H_ */
