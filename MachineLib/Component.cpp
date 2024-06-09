/**
 * @file Component.cpp
 * @author Frederick Fan
 *
 * Class for the components of a machine
 */

#include "pch.h"
#include "Component.h"
#include "Machine.h"
Component::Component()
{

}

/**
 * Install physics into each component, this function will just be empty in component
 * since not all components need to install physics, this function will be overridden in the necessary classes
 * @param world the b2world of the machine
 */
void Component::InstallPhysics(std::shared_ptr<b2World> world)
{
}

/**
 * Update the time
 * @param time time to update
 */
void Component::UpdateTime(double time)
{


    mTime +=time;

}
