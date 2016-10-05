#ifndef LOOPNODE_H_
#define LOOPNODE_H_
#include <vector>
#include "StructuredActivityNode.h"

namespace team4
{
class ExecutableNode;
class LoopNode : public StructuredActivityNode
{
public:
    static const std::string ELEMENT_TYPE;
    LoopNode();
    virtual ~LoopNode();
    bool isTestedFirst;
    bool decider;
    std::string init;
    std::string cond;
    std::vector<ExecutableNode*> test;
    std::vector<ExecutableNode*> setup;
    std::vector<ExecutableNode*> body;
    std::vector<std::string> elements;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //LOOPNODE_H_
