#ifndef ACTIVITY_NODE_H_
#define ACTIVITY_NODE_H_

#include "Element.h"
#include <vector>
namespace team4
{
class StructuredActivityNode;
class ActivityGroup;
class ActivityEdge;

class ActivityNode : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    ActivityNode();
    virtual ~ActivityNode();
    vector<ActivityEdge*> incoming;
    vector<ActivityEdge*> outgoing;
    StructuredActivityNode *instructedNode; //vnorenie
    vector<ActivityGroup*> inGroup;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
private:
    //vector<*ActivityEdge> _incoming;

};
};
#endif //ACTIVITY_NODE_H_
