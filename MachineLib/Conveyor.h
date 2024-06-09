/**
 * @file Conveyor.h
 * @author Frederick Fan
 *
 * A class for the conveyor component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSink.h"

/** A class for the conveyor component **/
class Conveyor : public Component, b2ContactListener
{
private:

    ///Position of the conveyor
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);

    /// the physics polygon for the conveyor image
    cse335::PhysicsPolygon mConveyor;

    ///The rotation sink
    RotationSink mSink;

    /// The shaft position
    wxPoint2DDouble mShaftPosition = wxPoint2DDouble(0,0);

    ///Speed of the conveyor
    double mSpeed = 0;

public:
    Conveyor(std::wstring imagesDir);

    /// Destructor
    virtual ~Conveyor() {}

    /** Copy constructor disabled */
    Conveyor(const Conveyor &) = delete;

    /** Assignment operator disabled */
    void operator=(const Conveyor &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetPosition(wxPoint2DDouble point);

    /**
     * Getter for the conveyor position
     * @return the conveyor position
     */
    wxPoint2DDouble GetPosition() { return mPosition;}


    void InstallPhysics(std::shared_ptr<b2World> world) override;


    /**
    * Get a pointer to the source object
    * @return Pointer to RotationSource object
    */
    RotationSink *GetSink() { return &mSink; }

    void Rotate(double rotation, double speed) override;

    /**
     * Getter for the shaft position
     * @return shaft position
     */
    wxPoint2DDouble GetShaftPosition() {return mShaftPosition;}

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    void AddContactListener(std::shared_ptr<ContactListener> contactListener) override;

    void ResetComponent() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
