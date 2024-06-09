/**
 * @file Component.h
 * @author Frederick Fan
 *
 * Class for the components of a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "PhysicsPolygon.h"
#include "box2d.h"
#include "ContactListener.h"

class Machine;
class RotationSink;

/** Class for the components of a machine */
class Component
{
private:


    ///the time
    double mTime = 0;


    ///The machine that the component is a part of
    Machine * mParentMachine = nullptr;

public:
    /// Constructor
    Component();

    /// Destructor
    virtual ~Component() {}

    /** Copy constructor disabled */
    Component(const Component&) = delete;

    /** Assignment operator disabled */
    void operator=(const Component &) = delete;

    /**
     * Draw the component
     * @param graphics the graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Update the time
     * @param time time to update
     */
    virtual void UpdateTime(double time);


    virtual void InstallPhysics(std::shared_ptr<b2World> world);

    /**
     * A setter for the component's parent machine
     * @param machine the machine to set to
     */
    void SetParentMachine(Machine *machine) { mParentMachine = machine;}


    /**
     * Add a contact listener
     * @param contactListener the contact listener to add
     */
    virtual void AddContactListener(std::shared_ptr<ContactListener> contactListener) {}


     /**
      * Rotate a component, empty because not all components can be rotated, will be overrided
      * @param rotation the rotation
      * @param speed speed of rotation
      */
     virtual void Rotate(double rotation, double speed) {}


     /**
      * Reset a component
      */
    virtual void ResetComponent() = 0;

    /**
     * Getter for the time
     * @return the time of the component
     */
     double GetTime(){return mTime;}


};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
