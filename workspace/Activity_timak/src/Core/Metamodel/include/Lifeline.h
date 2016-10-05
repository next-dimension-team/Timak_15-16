#ifndef LIFELINE_H_
#define LIFELINE_H_

#include "Element.h"

namespace team4
{
class InteractionFragment;
class Lifeline : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    Lifeline();
    virtual ~Lifeline();
    InteractionFragment *m_InteractionFragment;

    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //LIFELINE_H_
