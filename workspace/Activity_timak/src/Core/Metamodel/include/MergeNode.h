#ifndef  MERGENODE_H_
#define  MERGENODE_H_

#include "ControlNode.h"
#include <vector>

namespace team4
{
class ActivityEdge;
class MergeNode : public ControlNode
{
public:
    static const std::string ELEMENT_TYPE;
    MergeNode();
    virtual ~MergeNode();

    std::vector<ActivityEdge*> incoming;  //signal must come from less one input to become
    ActivityEdge *outgoing;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //MERGENODE_H_
