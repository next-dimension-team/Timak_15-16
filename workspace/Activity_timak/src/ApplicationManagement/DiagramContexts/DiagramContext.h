/*
 * DiagramContext.h
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#ifndef DIAGRAMCONTEXT_H_
#define DIAGRAMCONTEXT_H_

class DiagramContext
{
	public:
		DiagramContext();
		virtual ~DiagramContext();

		virtual void activateGui();
		virtual void initContent();
		virtual void releaseContent();
};

#endif /* DIAGRAMCONTEXT_H_ */
