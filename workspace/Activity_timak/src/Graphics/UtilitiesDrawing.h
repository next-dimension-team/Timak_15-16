/*
 * UtilitiesDrawing.h
 *
 *  Created on: 12.3.2013
 *      Author: Schade
 */

#ifndef UTILITIESDRAWING_H_
#define UTILITIESDRAWING_H_

#include <OgreImage.h>
#include <OgreTexture.h>
#include <string>

class UtilitiesDrawing {
public:
	static void writeToTexture(const std::string &str,
			Ogre::TexturePtr destTexture, Ogre::Image::Box destRectangle,
			Ogre::Font * font, const Ogre::ColourValue &color, char justify,
			bool wordwrap);
};

#endif /* UTILITIESDRAWING_H_ */
