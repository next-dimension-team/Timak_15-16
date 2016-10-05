#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "ConditionNode.h"
namespace team4
{
class Alt : public ConditionNode
{

public:
    static const std::string ELEMENT_TYPE;
    Alt();
    virtual ~Alt();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //CONDITION_NODE_H
