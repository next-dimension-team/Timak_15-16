#ifndef INTERACTION_H_
#define INTERACTION_H_


#include "InteractionFragment.h"

namespace team4
{
	class Action;
	class Lifeline;
class Interaction : public InteractionFragment
{
public:
    static const std::string ELEMENT_TYPE;
    Interaction();
    virtual ~Interaction();
    Lifeline *m_Lifeline;
    Action *m_Action;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //INTERACTION_H_
