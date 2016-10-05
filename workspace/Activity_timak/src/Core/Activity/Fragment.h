/*
 * Fragment.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef FRAGMENT_H_
#define FRAGMENT_H_

#include <string>

#include "../Container.h"

class FragmentCollection;


class Fragment: public Container
{
	friend class FragmentFactory;

	public:
		static const std::string ELEMENT_TYPE;

		virtual ~Fragment();

		FragmentCollection* getFragmentCollection();

		int getCollectionFragmentsCount();

	protected:
		Fragment();

	private:
		FragmentCollection* fragmentCollection;
};

#endif /* FRAGMENT_H_ */
