#ifndef DESERIALIZER_H_
#define DESERIALIZER_H_

#include <string>

namespace team4
{
class MetamodelElement;

class Deserializer
{
public:
	Deserializer(const std::string& A_file);
	Deserializer();
    bool run();

    bool callDeserializationType(team4::MetamodelElement* A_element, std::ofstream &A_stream);
private:
    std::string _fileName;
};
};

#endif /* DESERIALIZER_H_ */
