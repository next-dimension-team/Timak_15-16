#ifndef OPT_H_
#define OPT_H_

#include "ConditionNode.h"

namespace team4
{
class Opt : public ConditionNode
{
public:
    static const std::string ELEMENT_TYPE;
    Opt();
    virtual ~Opt();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //OPT_H_
