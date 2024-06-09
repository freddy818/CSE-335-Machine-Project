/**
 * @file Body.cpp
 * @author Frederick Fan
 */

#include "pch.h"
#include "Body.h"
#include "Polygon.h"

Body::Body()
{
    mSink.SetComponent(this);
}
/**
 * Draw the body component
 * @param graphics
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    GetPolygon()->Draw(graphics);
}


/**
 * Install physics into the body polygon
 * @param world the b2world for the machine
 */
void Body::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Rotate the body
 * @param rotation the rotation
 * @param speed speed of rotation
 */
void Body::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity(speed);
}

