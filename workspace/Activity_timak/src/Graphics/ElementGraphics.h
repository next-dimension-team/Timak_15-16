#ifndef ELEMENTGRAPHICS_H_
#define ELEMENTGRAPHICS_H_

class DrawingAlgorithm;
class Element;
#include <string>
namespace Metamodel
{
    class Element;
} /* namespace Metamodel */
namespace Ogre
{
    class ManualObject;
    class SceneNode;
    class Vector3;
} /* namespace Ogre */

class ElementGraphics
{
    public:
        ElementGraphics(Ogre::ManualObject* manualObject,
                        Ogre::SceneNode* sceneNode, DrawingAlgorithm* drawingAlgorihtm);
        virtual ~ElementGraphics();

        void virtual draw(const std::string& A_name);
        Ogre::SceneNode* getSceneNode();
        Ogre::ManualObject* getManualObject();

        Ogre::Vector3 virtual getConnectorBeginPoint(const std::string& A_name);
        Ogre::Vector3 virtual getConnectorEndPoint(const std::string& A_name);

        void virtual select(Element* elem);
        void virtual unselected(Element* elem);

        bool serialization(std::ofstream &A_stream);
        bool deserialization(std::ifstream &A_stream);

        DrawingAlgorithm* drawingAlgorihtm;
    protected:
        Ogre::SceneNode* node;
        Ogre::ManualObject* manualObject;

};

#endif /* ELEMENTGRAPHICS_H_ */
