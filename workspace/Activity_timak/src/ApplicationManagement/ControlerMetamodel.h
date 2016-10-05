#ifndef CONTROLERMETAMODEL_H_
#define CONTROLERMETAMODEL_H_

#include<string>
#include <vector>

namespace team4
{
    class MetaModel;
    class MetamodelElement;
    class ActivityNode;

    class ControlerMetamodel
    {
        private:
            MetaModel *_metamodel;
            int _idCount;

        public:

            ControlerMetamodel(MetaModel &A_metamodel);

            // return element index
            MetamodelElement* add(const std::string &A_type);

            // add edge, return index
            MetamodelElement* add(const std::string &A_type, ActivityNode *A_source, ActivityNode *A_target, const std::string& A_text);
            MetamodelElement* add(const std::string &A_type, const std::string& A_condition);
            MetamodelElement* add(const std::string &A_type, const std::string&  A_init, const std::string& A_cond);

            MetamodelElement* add(const std::string &A_type, const std::vector<std::string>& A_condition);

            MetamodelElement* get(int A_id);
            bool remove(int A_id);
            bool update(int A_id);


            bool removeAll();

            ~ControlerMetamodel();
    };
}

#endif /*CONTROLERMETAMODEL_H_ */
