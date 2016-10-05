#ifndef PAR_H_
#define PAR_H_

#include "ConditionNode.h"

namespace team4
{
class Par : public ConditionNode
{
public:
    static const std::string ELEMENT_TYPE;
    Par();
    virtual ~Par();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //PAR_H_
