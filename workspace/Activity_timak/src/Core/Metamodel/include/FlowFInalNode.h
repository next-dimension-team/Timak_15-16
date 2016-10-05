#ifndef FLOW_FINAL_NODE_H_
#define FLOW_FINAL_NODE_H_

#include "FinalNode.h"

namespace team4
{
class FlowFinalNode : public FinalNode
{

public:
    static const std::string ELEMENT_TYPE;
    FlowFinalNode();
    virtual ~FlowFinalNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //FLOW_FINAL_NODE_H_
