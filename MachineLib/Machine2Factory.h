/**
 * @file Machine2Factory.h
 * @author Frederick Fan
 *
 * Factory class for creating machine 2
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

class Machine;

/** Factory class for creating machine 2 */
class Machine2Factory
{
private:

    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:

    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine>Create();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
