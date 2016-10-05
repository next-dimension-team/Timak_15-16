#ifndef CLAUSE_H_
#define CLAUSE_H_

#include "Element.h"
#include <vector>
namespace team4
{
class ExecutableNode;

class Clause : public MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    Clause();
    virtual ~Clause();
    std::string condiotion;
    Clause *successorClause;
    ExecutableNode *test;
    ExecutableNode *body;


    std::vector<std::string> elements;
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);
};
};
#endif //CLAUSE_H_
