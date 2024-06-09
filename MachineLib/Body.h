/**
 * @file Body.h
 * @author Frederick Fan
 *
 * the class for the body component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include "Component.h"
#include "RotationSink.h"
#include "PhysicsPolygon.h"

/** the class for the body component */
class Body : public Component
{
private:

    ///The rotation sink for the component
    RotationSink mSink;

    ///the polygon image
    cse335::PhysicsPolygon mPolygon;

public:

    Body();

    /// Destructor
    virtual ~Body() {}

    /** Copy constructor disabled */
    Body(const Body &) = delete;

    /** Assignment operator disabled */
    void operator=(const Body &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world) override;


    /**
    * Getter for the polygon image
    * @return the polygon image
    */
    cse335::PhysicsPolygon * GetPolygon(){ return &mPolygon; }

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSink *GetSink() { return &mSink; }

    void Rotate(double rotation, double speed) override;

    /**
     * Reset the body components
     */
    void ResetComponent() override {};

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
