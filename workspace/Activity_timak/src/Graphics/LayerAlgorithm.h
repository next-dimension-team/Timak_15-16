/*
 * LayerAlgorithm.h
 *
 *  Created on: 10.3.2014
 *      Author: Schade
 */

#ifndef LAYERALGORITHM_H_
#define LAYERALGORITHM_H_

#include "DrawingAlgorithm.h"

class LayerAlgorithm: public DrawingAlgorithm
{
    public:
        LayerAlgorithm();
        virtual ~LayerAlgorithm();

        virtual void draw(const std::string& A_name);
        void select(Element* elem);
        void unselected(Element* elem);
};

#endif /* LAYERALGORITHM_H_ */
