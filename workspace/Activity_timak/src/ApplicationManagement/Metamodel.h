#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include "../HelperTeam4.h"
namespace team4
{
	class MetamodelElement;

    class MetaModel
    {
    public:
			MetaModel();
			~MetaModel();
        public:
            std::vector<MetamodelElement*> array;
            int getItemsCount();

    };
};
#endif //_MODEL_H_ */
