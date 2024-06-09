/**
 * @file RotationSink.cpp
 * @author Frederick Fan
 *
 * Class for rotation sinks
 */


#include "pch.h"
#include "RotationSink.h"
#include "Component.h"
#include "RotationSource.h"

/**
 * Rotate the component
 * @param rotation rotation
 * @param speed speed of rotation
 */
void RotationSink::Rotate(double rotation, double speed)
{
    mComponent->Rotate(rotation, speed);
}
