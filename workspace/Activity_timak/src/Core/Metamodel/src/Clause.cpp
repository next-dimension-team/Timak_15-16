#include "../include/Clause.h"
#include "../include/ExecutableNode.h"

namespace team4
{
const std::string Clause::ELEMENT_TYPE = "Clause";
Clause::Clause()
{
	condiotion = "";
    successorClause = NULL;
    test = NULL;
    body = NULL;
    setType(ELEMENT_TYPE);
    //elements = NULL;
    generateName();
}

Clause::~Clause()
{}

bool Clause::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
        if (!MetamodelElement::serialization(A_stream))
        {
            return false;
        }
        DEF_WRITE2FILE1(A_stream, condiotion);
        writeMetamodelElement2File(A_stream, successorClause);
        writeMetamodelElement2File(A_stream, test);
        writeMetamodelElement2File(A_stream, body);
        DEF_WRITE2FILE1(A_stream, elements.size());
                        for (auto i: elements)
                        {
                        	DEF_WRITE2FILE1(A_stream, i);
                        }
        return true;
    }
    return false;
}
bool Clause::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
