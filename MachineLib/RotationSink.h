/**
 * @file RotationSink.h
 * @author Frederick Fan
 *
 * Class for rotation sinks
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H

class Component;
class RotationSource;

/** Class for rotation sinks */
class RotationSink
{
private:

    /// the rotation
    double mRotation = 0;

    ///The parent component of the sink
    Component * mComponent = nullptr;

    ///The source for the sink
    RotationSource * mSource = nullptr;

public:

    ///default constructor
    RotationSink() {}

    /// Copy constructor (disabled)
    RotationSink(const RotationSink &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSink &) = delete;

    /**
     * setter for the rotation of the sink
     * @param rotation rotation to set to
     */
    void SetRotation(double rotation) {mRotation = rotation;}

    /**
     * Getter for the rotation of the sink
     * @return rotation to set to
     */
    double GetRotation() {return mRotation;}

    /**
     * set the component for the sink
     * @param component the component to set to
     */
     void SetComponent(Component * component) {mComponent = component;}

     void Rotate(double rotation, double speed);

     /**
      * Setter for the sink's source
      * @param source the sink's source
      */
      void SetSource(RotationSource* source) { mSource = source;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
