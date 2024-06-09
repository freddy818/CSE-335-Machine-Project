/**
 * @file RotationSource.h
 * @author Frederick Fan
 *
 * Class for rotation sources
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

class RotationSink;
class Component;

/** Class for rotation sources **/
class RotationSource
{
private:
    /// The sinks of this source
    std::vector<RotationSink *> mSinks;

    ///The parent component of the source
    Component * mComponent = nullptr;

public:

    ///Default constructor
    RotationSource() {}

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    void Rotate(double rotation, double speed);


    /**
     * set the component for the sink
     * @param component the component to set to
     */
    void SetComponent(Component * component) {mComponent = component;}

    void AddSink(RotationSink *sink  );

    /**
     * Getter for the component
     * @return the component
     */
    Component * GetComponent() {return mComponent;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
