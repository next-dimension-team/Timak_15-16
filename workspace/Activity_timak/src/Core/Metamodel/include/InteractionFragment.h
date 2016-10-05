#ifndef INTERACTION_FRAGMENT_H_
#define INTERACTION_FRAGMENT_H_

#include "Element.h"

namespace team4
{
class InteractionFragment : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    InteractionFragment();
    virtual ~InteractionFragment();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //INTERACTION_FRAGMENT_H_
