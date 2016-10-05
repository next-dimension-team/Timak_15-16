/*
 * FragmentCollection.h
 *
 *  Created on: 10.11.2013
 *      Author: Schade
 */

#ifndef FRAGMENTCOLLECTION_H_
#define FRAGMENTCOLLECTION_H_


class Fragment;


#include <vector>


class FragmentCollection
{
	public:
		FragmentCollection();
		~FragmentCollection();

		Fragment* getFirst();
		void add(Fragment* f);
		std::vector<Fragment*> getAll();
		int getCount();

		bool isExpanded();
		void setExpanded(bool expanded);

	private:
		std::vector<Fragment*> fragments;
		bool expanded;
};

#endif /* FRAGMENTCOLLECTION_H_ */
