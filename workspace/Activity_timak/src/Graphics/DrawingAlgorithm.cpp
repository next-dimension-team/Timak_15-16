/*
 * DrawingAlgorithm.cpp
 *
 *  Created on: 16.6.2013
 *      Author: Schade
 */

#include "DrawingAlgorithm.h"
#include "../HelperTeam4.h"

DrawingAlgorithm::DrawingAlgorithm()
{
	_size = 0;
	widthE = 0;
	heightE = 0;
}

DrawingAlgorithm::~DrawingAlgorithm()
{}

void DrawingAlgorithm::draw(const std::string& A_name)
{}

void DrawingAlgorithm::select(Element* elem)
{
    //DEF_BEGIN;
}

void DrawingAlgorithm::unselected(Element* elem)
{

}

int DrawingAlgorithm::getSize()
{
	return _size;
}
int DrawingAlgorithm::setSize(int A_size)
{
	_size = A_size;
}
