/*
 * ElementCollection.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef ELEMENTCOLLECTION_H_
#define ELEMENTCOLLECTION_H_

#include <map>
#include <string>
#include <vector>

#include "../Core/Layer.h"
#include "../Core/LayerBookmark.h"

class Class;
namespace Metamodel {
class Space;
} /* namespace Metamodel */

namespace team4
{
	class ControlerMetamodel;
	class MetaModel;
	class MetamodelElement;
	class ActivityNode;
}

class ElementCollection
{
	public:
		static ElementCollection* getInstance();

		virtual ~ElementCollection();

		std::pair<Element*, team4::MetamodelElement*> findElement(const std::string& A_name);
		Element* findElement(Metamodel::Element* data);
		Layer* findLayerOfClass(Class* cla);
		Layer* findLayerOfElement(Element* elem);
		Container* findContainerOfElement(Element* elem);

		std::pair<Element*, team4::MetamodelElement*> insertElementTeam4(Element * elem, const std::string &A_type);
		std::pair<Element*, team4::MetamodelElement*> insertElementTeam4(Element * elem, const std::string &A_type, team4::ActivityNode *A_source, team4::ActivityNode *A_target, const std::string& A_text);
		std::pair<Element*, team4::MetamodelElement*> insertElementTeam4(Element * elem, const std::string &A_type,	const std::string&  A_init, const std::string& A_cond);
		std::pair<Element*, team4::MetamodelElement*> insertElementTeam4(Element * elem, const std::string &A_type, const std::vector<std::string>& A_condition);

		std::vector<Layer*> getLayers();
		std::vector<std::pair<Element*, team4::MetamodelElement*>> getConnectors();
		LayerBookmark* findBookmark(std::string name);
		std::vector<LayerBookmark*> getLayerBookmarks();
		void removeElement(const std::string& A_Name);
		void removeAllElements();
		Metamodel::Space* getSpace();
		std::pair<Element*, team4::MetamodelElement*> searchCloseElement(Ogre::Vector2* point);
		std::pair<Element*, team4::MetamodelElement*> searchCloseFragment(Ogre::Vector2* point);
		void insertElementToFragment(const std::string &A_name, Ogre::Vector2* centerPoint);
		std::vector<std::pair<Element*, team4::MetamodelElement*>> getAllElements();
		//std::vector<Element*> getAllElementsTeam4();
		bool isNode(std::string type);
		void setSelectedLayers();
		void setNormalLayers();
		void DecrementLayer();
		void IncrementLayer();
		void selectLayer(Layer* lay);
		Layer* getSelectedLayer();
		int getDefaultWidthOfFragment(Ogre::Vector2* point);
		int getDefaultHeightOfFragment(Ogre::Vector2* point);
		Ogre::Vector2* getDefaultCenterOfFragment(Ogre::Vector2* point);
		void setModel(std::map<std::string, std::pair<Element* ,int>> &A_elements);

	private:
		team4::ControlerMetamodel *_controlerMetamodel;
		team4::MetaModel *_metamodel;
		typedef std::map<std::string, std::pair<Element* ,int>>::iterator it_type;
		static ElementCollection* singletonObject;

		//std::map<std::string, Element*> elements;

		std::map<std::string, std::pair<Element* ,int>> elements1;

		Metamodel::Space* space;

		ElementCollection();
};

#endif /* ELEMENTCOLLECTION_H_ */
