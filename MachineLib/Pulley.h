/**
 * @file Pulley.h
 * @author Frederick Fan
 *
 * Class for the pulley component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "Component.h"
#include "RotationSink.h"
#include "RotationSource.h"
#include "Polygon.h"

/** Class for the pulley component **/
class Pulley : public Component
{
private:
    /// The rotation sink for the pulley
    RotationSink mSink;

    ///The rotation source for the pulley
    RotationSource mSource;

    ///The rotation for the pulley
    double mRotation = 0;

    ///The position of the pulley
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);

    ///The polygon for the pulley
    cse335::Polygon mPolygon;

    ///Radius of the pulley
    double mRadius = 0;

    ///Speed of the pulley
    double mSpeed = 0;

    ///A pulley that this pulley is connected to
    std::shared_ptr<Pulley> mConnectedPulley = nullptr;

public:

    ///default constructor
    Pulley(double radius);

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    ///virtual destructor
    virtual ~Pulley() {}

    /// Assignment operator (disabled)
    void operator=(const Pulley &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetPosition(wxPoint2DDouble point);

    void UpdateTime(double time) override;

    /**
      * Getter for the polygon image
      * @return the polygon image
      */
    cse335::Polygon * GetPolygon(){ return &mPolygon; }


    /**
   * Get a pointer to the sink object
   * @return Pointer to RotationSource object
   */
    RotationSink *GetSink() { return &mSink; }

    /**
    * Get a pointer to the source object
    * @return Pointer to RotationSource object
    */
    RotationSource *GetSource() { return &mSource; }

    void Rotate(double rotation, double speed) override;

    void Drive(std::shared_ptr<Pulley> pulley);

    /**
     * Set two pulleys to be connected to each other
     * @param pulley the pulley to connected
     */
    void SetConnectedPulley(std::shared_ptr<Pulley> pulley) {mConnectedPulley = pulley;}

    /**
     * Get the position of a pulley
     * @return the position of a pulley
     */
    wxPoint2DDouble GetPosition(){ return mPosition; }


    void ResetComponent() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
