#ifndef MERGEA_H_
#define MERGEA_H_

class Layer;

#include "../Element.h"

class Merge: public Element
{
    friend class MergeFactory;

public:
    static const std::string ELEMENT_TYPE;
    virtual ~Merge();

protected:
    Merge();
};

#endif
