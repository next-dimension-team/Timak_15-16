#ifndef FINAL_NODE_H_
#define FINAL_NODE_H_

#include "ControlNode.h"

namespace team4
{
class FinalNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    FinalNode();
    virtual ~FinalNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //FINAL_NODE_H_
