/*
 * FragmentAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef FRAGMENTALGORITHM_H_
#define FRAGMENTALGORITHM_H_

#include "../DrawingAlgorithm.h"

namespace Ogre
{
class FontPtr;
} /* namespace Ogre */

class ContainerGraphics;
class Fragment;

class FragmentAlgorithm: public DrawingAlgorithm
{
public:
    FragmentAlgorithm();
    virtual ~FragmentAlgorithm();





    virtual void draw(const std::string& A_name);
    virtual void select(Element* elem);
    virtual void unselected(Element* elem);
    static void cleanUp();

private:
    void drawAlt(const std::string& A_name);
    void drawSeq(const std::string& A_name);
    void drawLoop(const std::string& A_name);
    Fragment* elem;
    ContainerGraphics* elemGraphics;

    double headerLineHeight;
    double bookmarkFieldWidth;
    double typeFieldWidth;
    double textureSizeScale;

    void initTextures(Fragment* elem,float count);
    void initMaterials(Fragment* elem, Element* helpElement,float count);
    void initFonts();

    static Ogre::FontPtr BOOKMARK_FONT;
    static Ogre::FontPtr TYPE_FONT;
    static Ogre::FontPtr CONDITION_FONT;
};

#endif /* FRAGMENTALGORITHM_H_ */
