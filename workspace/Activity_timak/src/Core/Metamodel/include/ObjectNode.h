#ifndef OBJECTNODE_H_
#define OBJECTNODE_H_

#include "ActivityNode.h"

namespace team4
{
class ObjectNode : public ActivityNode
{
public:
    static const std::string ELEMENT_TYPE;
    ObjectNode();
    virtual ~ObjectNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //OBJECTNODE_H_
