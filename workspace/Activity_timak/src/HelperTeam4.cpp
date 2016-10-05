#include "HelperTeam4.h"
#include <ctime>
#include <iostream>
#include <sstream>
 #include <windows.h>
using namespace std;

namespace Helpers
{

bool fileExist(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
bool folderExist(const std::string& A_folder)
{
    DWORD ftyp = GetFileAttributesA(A_folder.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;   // this is a directory!
    }
    return false;    // this is not a directory!
}

std::string getActualTime(const std::string& A_format)
{
    std::string time_string = "";
    time_t now = time(0);
    tm *ltm = localtime(&now);

    time_string += NumberToString(1900 + ltm->tm_year) + "_";
    time_string += NumberToString(1 + ltm->tm_mon) + "_";
    time_string += NumberToString(ltm->tm_mday) + "_";
    time_string += NumberToString(1 + ltm->tm_hour) + "_";
    time_string += NumberToString(1 + ltm->tm_min) + "_";
    time_string += NumberToString(1 + ltm->tm_sec);
    return time_string;
}


template <typename T>
std::string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}
bool createDirectory(const std::string& A_DirName)
{
       if(!CreateDirectory(A_DirName.c_str(), NULL))
       {
           return false;
       }
       else
       {
    	   return true;
       }
	return false;
}

}
