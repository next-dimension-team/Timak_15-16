#ifndef INTERACTION_OPERATOR_H_
#define INTERACTION_OPERATOR_H_

#include "Element.h"

namespace team4
{
class InteractionOperator : MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    InteractionOperator();
    virtual ~InteractionOperator();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //INTERACTION_OPERATOR_H_
