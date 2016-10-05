#ifndef ACTIVITY_H_
#define ACTIVITY_H_

#include "Behavior.h"

namespace team4
{
class ActivityNode;
class ActivityEdge;

class Activity: public Behavior
{
public:
    static const std::string ELEMENT_TYPE;
    Activity();
    virtual ~Activity();
    bool isReadOnly;
    bool isSingleExecution;
    ActivityNode *node;
    ActivityEdge *edge;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif
