#include "Metamodel.h"

#include <iostream>

namespace team4
{
    MetaModel::MetaModel()
    {
    }

    MetaModel::~MetaModel()
    {
        for (int i=0; i < (int)array.size(); i++)
        {
            //correct deallocation
            delete array[i];
        }
        array.clear();
    }

    int MetaModel::getItemsCount()
    {
        return int(array.size());
    }


}
