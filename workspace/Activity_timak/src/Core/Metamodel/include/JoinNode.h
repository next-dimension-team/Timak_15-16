#ifndef JOINNODE_H_
#define JOINNODE_H_

#include "ControlNode.h"

#include <vector>

namespace team4
{
class ActivityEdge;
class JoinNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    JoinNode();
    virtual ~JoinNode();

    std::vector<ActivityEdge*> incoming;  // wait for all input signals
    ActivityEdge *outgoing;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //JOINNODE_H_
