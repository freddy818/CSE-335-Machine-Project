/**
 * @file Hamster.h
 * @author Frederick Fan
 *
 * class for hamsters
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include <vector>
#include "RotationSource.h"
#include "Component.h"

class Polygon;
class PhysicsPolygon;

/** Class for hamsters */
class Hamster : public Component, public b2ContactListener
{
private:
    ///A bool to represent if the hamster is asleep
    bool mIsAsleep = true;

    ///A collection of hamster polygons
    std::vector<std::shared_ptr<cse335::Polygon>> mHamsters;

    ///The position of the hamster
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);

    ///Speed of the hamster
    double mSpeed = 0;

    ///A physics polygon for the cage
    cse335::PhysicsPolygon mCage;

    ///A polygon for the wheel
    cse335::Polygon mWheel;

    ///The hamster shaft position
    wxPoint2DDouble mHamsterShaft = wxPoint2DDouble(0,0);

    ///a bool representing if the hamster is initially running
    bool mInitiallyRunning = false;

    ///The rotation
    double mRotation = 0;

    ///The rotation source object
    RotationSource mSource;


public:

    Hamster(std::wstring imagesDir);

    /// Destructor
    virtual ~Hamster() {}

    /** Copy constructor disabled */
    Hamster(const Hamster &) = delete;

    /** Assignment operator disabled */
    void operator=(const Hamster &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void UpdateTime(double time) override;

    void SetPosition(wxPoint2DDouble point);

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void AddContactListener(std::shared_ptr<ContactListener> contactListener) override;

    /**
     * Getter for the shaft position
     * @return shaft position
     */
    wxPoint2DDouble GetShaftPosition() {return mHamsterShaft;}


    void SetInitiallyRunning(bool run);

    /**
     * Setter for the speed
     * @param speed the speed to set to
     */
    void SetSpeed(double speed) {mSpeed = speed;}

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    void BeginContact(b2Contact *contact) override;


    void ResetComponent() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
