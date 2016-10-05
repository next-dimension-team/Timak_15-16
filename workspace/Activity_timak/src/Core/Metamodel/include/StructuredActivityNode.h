#ifndef STRUCTURED_ACTIVITY_NODE_H_
#define STRUCTURED_ACTIVITY_NODE_H_

#include "Action.h"
#include "ActivityGroup.h"

namespace team4
{
class ActivityNode;
class ActivityEdge;
class Variable;

class StructuredActivityNode : public Action //, public ActivityGroup
{
public:
    static const std::string ELEMENT_TYPE;
    StructuredActivityNode();
    virtual ~StructuredActivityNode();
    bool mustIsolate;
    ActivityNode *node;
    Variable *variable;
    ActivityEdge *edge;
    std::vector<std::string> elements;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //STRUCTURED_ACTIVITY_NODE_H_
