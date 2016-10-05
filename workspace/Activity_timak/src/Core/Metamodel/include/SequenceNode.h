#ifndef  SEQUENCENODE_H_
#define  SEQUENCENODE_H_

#include "StructuredActivityNode.h"

namespace team4
{
class ExecutableNode;
class SequenceNode : public StructuredActivityNode
{
public:
    static const std::string ELEMENT_TYPE;
    SequenceNode();
    virtual ~SequenceNode();
    ExecutableNode *executableNode;
    ExecutableNode *m_ExecutableNode;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //SEQUENCENODE_H_
