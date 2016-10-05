#ifndef DECISIONNODE_H_
#define DECISIONNODE_H_

#include "ControlNode.h"

namespace team4
{
class ActivityEdge;
class DecisionNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    DecisionNode();
    virtual ~DecisionNode();

    vector<ActivityEdge*> outgoing;
    ActivityEdge *incoming;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //DECISIONNODE_H_
