/*
 *      Author: Bc. Andrej Železòák
 *      Email: azeleznak@gmail.com
 */

#ifndef C_ELEMENT_H_
#define C_ELEMENT_H_

using namespace std;
#include <string>
#include <fstream>
#include "../../../HelperTeam4.h"


namespace team4
{
class MetamodelElement
{
public:
    static const std::string ELEMENT_TYPE;
    virtual ~MetamodelElement();

    MetamodelElement* allOwnedElements();
    bool mustBeOwned();
    std::string getName();
    int getId();
    void setId(int A_id);
    void setName(std::string A_name);
    std::string getType();
    void draw();
    MetamodelElement();
    void setType(std::string A_type);

    void generateName();
    std::string type;
    int id;
    std::string name;
    void Log();
    bool serialization(std::ofstream &A_stream);
    bool deserialization(std::ifstream &A_stream);


protected:
};

void writeMetamodelElement2File(std::ofstream &A_stream, team4::MetamodelElement* A_element);



};

#endif
