#ifndef COMBINEDFRAGMENT_H_
#define COMBINEDFRAGMENT_H_

#include "InteractionFragment.h"

namespace team4
{
class InteractionOperator;
class InteractionOperand;

class CombinedFragment : public InteractionFragment
{

public:
    static const std::string ELEMENT_TYPE;
    CombinedFragment();
    virtual ~CombinedFragment();
    InteractionOperand *m_InteractionOperand;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
private:
    InteractionOperator *_operator;

};
};
#endif //COMBINEDFRAGMENT_H_
