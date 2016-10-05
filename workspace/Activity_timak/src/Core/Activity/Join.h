#ifndef JOIN_H_
#define JOIN_H_

class Layer;

#include "../Element.h"

class Join: public Element {
	friend class JoinFactory;

	public:
		static const std::string ELEMENT_TYPE;
		virtual ~Join();

	protected:
		Join();
};

#endif
