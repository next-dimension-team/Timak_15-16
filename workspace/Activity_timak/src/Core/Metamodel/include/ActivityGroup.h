#ifndef ACTIVITY_GROUP_H_
#define ACTIVITY_GROUP_H_

#include <string>
#include "Element.h"

namespace team4
{
class ActivityGroup : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    ActivityGroup();
    virtual ~ActivityGroup();
    ActivityGroup *m_ActivityGroup;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);

};
};
#endif //ACTIVITY_GROUP_H_
