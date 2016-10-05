#ifndef _HELPER_TEAM4_H_
#define _HELPER_TEAM4_H_

#include <iostream>
#include "windows.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#include <string>
#include <direct.h>
#include  <io.h>
#include <direct.h>
#include <sstream>
#include <sys/stat.h>

//#define GetCurrentDir std::string(_getcwd)

#define DEF_BEGIN std::cout << "LOG_BEGIN | " << __FUNCTION__  << "() | " << (__FILE__) << " : "   << (__LINE__) << std::endl;

#define DEF_END  std::cout << "LOG_END | " << __FUNCTION__  << "() | " << (__FILE__) << " : "   << (__LINE__) << std::endl;

#define DEF_ERROR(value) std::cout << "LOG_ERROR | " << value  << " | " << __FUNCTION__  << "() | " << (__FILE__) << " : "   << (__LINE__) << std::endl;
#define DEF_DEBUG(value) std::cout << "LOG_DEBUG | " << value  << " | " << __FUNCTION__  << "() | " << (__FILE__) << " : "   << (__LINE__) << std::endl;

#define DEFL std::cout << "LOG | " << __FUNCTION__  << "() | " << (__FILE__) << " : "   << (__LINE__) <<  std::endl;

#define DEF_LOG(value) std::cout << #value << " = " << value <<  std::endl;

#define DEF_WRITE2FILE1(file, value)  							file << value  << "\n";
#define DEF_WRITE2FILE2(file, value1, value2) 					file << value1 << "\t" << value2 << "\n";
#define DEF_WRITE2FILE3(file, value1, value2, value3) 			file << value1 << "\t" << value2 << "\t" << value3 << "\n";
#define DEF_WRITE2FILE4(file, value1, value2, value3, value4) 	file << value1 << "\t" << value2 << "\t" << value3 << "\t" << value4 << "\n";

#define DEF_READFROMFILE1(file, value)  							file >> value;
#define DEF_READFROMFILE2(file, value1, value2) 					file >> value1 >> value2;
#define DEF_READFROMFILE3(file, value1, value2, value3) 			file >> value1 >> value2 >> value3;
#define DEF_READFROMFILE4(file, value1, value2, value3, value4) 	file >> value1 >> value2 >> value3 >> value4;



#endif //_HELPER_TEAM4_H_ */


namespace Helpers
{

	bool fileExist(const std::string& name);

	bool folderExist(const std::string& A_folder);

	std::string getActualTime(const std::string& A_format);

	template <typename T> std::string NumberToString ( T A_Number );

	bool createDirectory(const std::string& A_DirName);


}
