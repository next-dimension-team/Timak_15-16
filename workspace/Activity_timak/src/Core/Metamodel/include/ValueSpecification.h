#ifndef VALUE_SPECIFICATION_H
#define VALUE_SPECIFICATION_H

#include "Element.h"

namespace team4
{
class ValueSpecification : public MetamodelElement
{
private:
    std::string _value;
public:
    static const std::string ELEMENT_TYPE;
    ValueSpecification(const std::string &A_value);
    void set(const std::string &A_value);
    std::string get();
    virtual ~ValueSpecification();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif // VALUE_SPECIFICATION_H
