#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include <string>
#include "Element.h"

namespace team4
{
class Behavior : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    Behavior();
    virtual ~Behavior();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //BEHAVIOR_H_
