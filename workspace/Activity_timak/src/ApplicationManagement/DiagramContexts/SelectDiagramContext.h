/*
 * SelectDiagramContext.h
 *
 *  Created on: 3.12.2013
 *      Author: Schade
 */

#ifndef SELECTDIAGRAMCONTEXT_H_
#define SELECTDIAGRAMCONTEXT_H_

class SelectDiagramWindow;

#include "DiagramContext.h"

class SelectDiagramContext: public DiagramContext {
	public:
		SelectDiagramContext();
		virtual ~SelectDiagramContext();

		virtual void activateGui();
		virtual void initContent();

		SelectDiagramWindow* getWindowSelectDiagram();
		void closeSelectDiagramWindow();

	private:
		SelectDiagramWindow* windowSelectDiagram;
};

#endif /* SELECTDIAGRAMCONTEXT_H_ */
