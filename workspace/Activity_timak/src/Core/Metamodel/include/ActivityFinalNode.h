#ifndef ACTIVITY_FINAL_NODE_H_
#define ACTIVITY_FINAL_NODE_H_

#include "FinalNode.h"
namespace team4
{
class ActivityFinalNode : public FinalNode
{

public:
    static const std::string ELEMENT_TYPE;
    ActivityFinalNode();
    virtual ~ActivityFinalNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //ACTIVITY_FINAL_NODE_H_
