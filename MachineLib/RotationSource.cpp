/**
 * @file RotationSource.cpp
 * @author Frederick Fan
 *
 * Class for rotation sources
 */

#include "pch.h"
#include "RotationSource.h"
#include "RotationSink.h"

/**
 * Rotate the sink
 * @param rotation the rotation
 * @param speed the speed to rotate
 */
void RotationSource::Rotate(double rotation, double speed)
{
    for (auto sink : mSinks)
    {
        sink->Rotate(rotation, speed);
    }

}

/**
 * Add a sink to this source
 * @param sink the sink to add
 */
void RotationSource::AddSink(RotationSink * sink)
{
    mSinks.push_back(sink);
    sink->SetSource(this);
}
