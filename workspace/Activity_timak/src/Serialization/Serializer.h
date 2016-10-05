#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <string>

#define DEF_FILE_NAME std::string("3DUML_Export")
class Element;
namespace team4
{
class MetamodelElement;
class Serializer
{
public:
    Serializer(const std::string& A_file);
    Serializer();
    bool run();

    bool callSerializationType(const std::pair<Element*, team4::MetamodelElement*>& A_element, std::ofstream &A_stream);
private:
    std::string _fileName;
};
};
#endif /* SERIALIZER_H_ */
