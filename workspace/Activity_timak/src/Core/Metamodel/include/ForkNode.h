#ifndef FORK_NODE_H_
#define FORK_NODE_H_

#include "ControlNode.h"
#include <vector>

namespace team4
{
class ActivityEdge;
class ForkNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    ForkNode();
    virtual ~ForkNode();

    ActivityEdge *incoming;
    std::vector<ActivityEdge*> outgoing; // start few process parallelly
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //FORK_NODE_H_
