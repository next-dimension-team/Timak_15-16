#ifndef CONTROLNODEA_H_
#define CONTROLNODEA_H_

#include "ActivityNode.h"

namespace team4
{
class ControlNode : public ActivityNode
{
public:
    static const std::string ELEMENT_TYPE;
    ControlNode();
    virtual ~ControlNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //CONTROLNODE_H_
