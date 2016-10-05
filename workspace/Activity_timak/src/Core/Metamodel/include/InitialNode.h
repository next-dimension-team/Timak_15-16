#ifndef INITIAL_NODE_H_
#define INITIAL_NODE_H_

#include "ControlNode.h"

namespace team4
{
class InitialNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    InitialNode();
    virtual ~InitialNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //INITIAL_NODE_H_
