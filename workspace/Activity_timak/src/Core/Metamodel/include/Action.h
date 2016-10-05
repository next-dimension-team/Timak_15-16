
#ifndef EXACUTABLE_NODE_H_
#define EXACUTABLE_NODE_H_

#include "ExecutableNode.h"

namespace team4
{
class Constraint;

class Action : public ExecutableNode
{
public:
    static const std::string ELEMENT_TYPE;
    Action();
    virtual ~Action();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);


    bool isLocallyReentrant;
    Constraint *localPostcondition;
    Constraint *m_Constraint;
    Constraint *localPrecondition;
};
};
#endif
