/*
 * DrawingAlgorithm.h
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#ifndef DRAWINGALGORITHM_H_
#define DRAWINGALGORITHM_H_

#include <string>
class Element;


class DrawingAlgorithm
{
	private:
		int _size;

    public:
		int widthE;
		int heightE;
		int getSize();
		int setSize(int A_size);
        DrawingAlgorithm();
        virtual ~DrawingAlgorithm();

        virtual void draw(const std::string& A_name);
        virtual void select(Element* elem);
        virtual void unselected(Element* elem);
};

#endif /* DRAWINGALGORITHM_H_ */
