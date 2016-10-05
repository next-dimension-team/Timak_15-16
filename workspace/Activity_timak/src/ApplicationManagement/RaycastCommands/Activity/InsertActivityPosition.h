/*
 * InsertActivityPosition.h
 *
 *  Created on: 1.3.2014
 *      Author: Schade
 */

#ifndef INSERTACTIVITYPOSITION_H_
#define INSERTACTIVITYPOSITION_H_

#include <OgrePrerequisites.h>
#include <vector>

#include "../../../Core/Container.h"
#include "../RaycastCommand.h"

namespace team4
{
	class MetamodelElement;
}

class InsertActivityPosition: public RaycastCommand
{
public:
    InsertActivityPosition();
    virtual ~InsertActivityPosition();

    bool virtual conditionsAccepted();
    bool virtual check();
    void virtual action();
    bool virtual stop();
    void virtual postProcessAction();


private:
    Ogre::Real distance;
    std::vector<std::pair<Container*, team4::MetamodelElement*>> containers;

    std::pair<Container*, team4::MetamodelElement*> getSelectedContainer();
};

#endif /* INSERTACTIVITYPOSITION_H_ */
