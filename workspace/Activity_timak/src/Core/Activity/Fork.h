#ifndef FORK_H_
#define FORK_H_

class Layer;

#include "../Element.h"

class Fork : public Element
{
    friend class ForkFactory;

public:
    static const std::string ELEMENT_TYPE;
    virtual ~Fork();

protected:
    Fork();
};

#endif
