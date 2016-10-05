#ifndef ACTIVITY_EDGE_H
#define ACTIVITY_EDGE_H

#include "Element.h"

namespace team4
{
class ActivityNode;
class ValueSpecification;

class ActivityEdge : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    ActivityEdge();
    virtual  ~ActivityEdge();
    std::string text;
    ActivityNode *source;
    ActivityNode *target;

    ValueSpecification *guard; // text v hranatych zatvorkach nejaky string
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif
