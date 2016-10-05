/*
 * ActivityDiagramContext.h
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#ifndef ACTIVITYDIAGRAMCONTEXT_H_
#define ACTIVITYDIAGRAMCONTEXT_H_

class ActivityWindow;

#include "DiagramContext.h"

class ActivityDiagramContext: public DiagramContext {
	public:
		ActivityDiagramContext();
		virtual ~ActivityDiagramContext();

		virtual void activateGui();
		virtual void initContent();
		virtual void releaseContent();

		ActivityWindow* getActivityWindow();
		void closeActivityWindow();

	private:
		ActivityWindow* activityWindow;
};

#endif /* ACTIVITYDIAGRAMCONTEXT_H_ */
