#include "../include/ActivityEdge.h"

#include "../include/Element.h"
#include "../include/ActivityNode.h"
#include "../include/ValueSpecification.h"

namespace team4
{
const std::string ActivityEdge::ELEMENT_TYPE = "ActivityEdge";

ActivityEdge::ActivityEdge()
{
    target = NULL;
    source = NULL;
    guard = NULL;
    text = "";
    setType(ELEMENT_TYPE);
    generateName();

}

ActivityEdge::~ActivityEdge()
{}

bool ActivityEdge::serialization(std::ofstream &A_stream)
{
    if (A_stream.is_open())
    {
    	if (!MetamodelElement::serialization(A_stream))
    	{
    		return false;
    	}
    	DEF_WRITE2FILE1(A_stream, text);
    	writeMetamodelElement2File(A_stream, target);
		writeMetamodelElement2File(A_stream, source);
		writeMetamodelElement2File(A_stream, guard);
        return true;
    }
    return false;
}
bool ActivityEdge::deserialization(std::ifstream &A_stream)
{
    if (A_stream.is_open())
    {
        //A_stream >> this->type;
        return MetamodelElement::deserialization(A_stream) && true;
    }
    return false;
}
}
