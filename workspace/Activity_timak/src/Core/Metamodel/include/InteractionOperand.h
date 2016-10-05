
#ifndef INTERACTION_OPERAND_H_
#define INTERACTION_OPERAND_H_

#include "Element.h"

namespace team4
{
class InteractionFragment;

class InteractionOperand : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    InteractionOperand();
    virtual ~InteractionOperand();
    InteractionFragment *m_InteractionFragment;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //INTERACTION_OPERAND_H_
