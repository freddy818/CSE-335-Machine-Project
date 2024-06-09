/**
 * @file Machine.h
 * @author Frederick Fan
 *
 * class for a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include "box2d.h"

class ContactListener;
class Component;
class MachineSystemActual;

/** Class for a machine **/

class Machine
{
private:

    ///A collection of the components in the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    ///The machine Id
    int mMachineId = 0;

    /// The box2d world
    std::shared_ptr<b2World> mWorld = nullptr;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener = nullptr;



public:
    Machine(int machineId);

    /// Destructor
    virtual ~Machine() {}

    /// Copy constructor disabled
    Machine(const Machine &) = delete;

    /// Assignment operator disabled
    void operator=(const Machine &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void AddComponent(std::shared_ptr<Component> component);

    void Update(double elapsed);

    void Reset();

    void InstallPhysics();


};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
