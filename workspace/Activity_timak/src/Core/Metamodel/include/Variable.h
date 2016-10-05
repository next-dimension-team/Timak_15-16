#ifndef VARIABLE_H
#define VARIABLE_H

#include "Element.h"

namespace team4
{
class Variable : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    Variable();
    virtual ~Variable();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //VARIABLE_H
