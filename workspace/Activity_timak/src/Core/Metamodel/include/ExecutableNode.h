#ifndef EXECUTABLE_NODE_H_
#define EXECUTABLE_NODE_H_

#include "ActivityNode.h"

namespace team4
{
class ExecutableNode : public ActivityNode
{
public:
    static const std::string ELEMENT_TYPE;
    std::string executable;
    ExecutableNode();
    virtual ~ExecutableNode();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //EXECUTABLE_NODE_H_
