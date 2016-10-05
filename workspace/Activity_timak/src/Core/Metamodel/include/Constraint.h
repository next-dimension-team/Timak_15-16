#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "Element.h"

namespace team4
{
class Constraint : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    Constraint();
    virtual ~Constraint();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //CONSTRAINT_H_
