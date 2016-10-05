#ifndef ConditionNode_H_
#define ConditionNode_H_

#include "StructuredActivityNode.h"
#include "Clause.h"
namespace team4
{
//class Clause;

class ConditionNode : public StructuredActivityNode
{

public:
    static const std::string ELEMENT_TYPE;
    ConditionNode();
    virtual ~ConditionNode();
    bool isAssured;
    bool isDeterminate;
    std::vector<Clause*> cluase;

    Clause *m_Clause;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //ConditionNode_H_
