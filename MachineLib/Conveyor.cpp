/**
 * @file Conveyor.cpp
 * @author Frederick Fan
 *
 * A class for the conveyor component
 */

#include "pch.h"
#include "Conveyor.h"

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Constructor
 * @param imagesDir the image directory
 */
Conveyor::Conveyor(std::wstring imagesDir)
{
    mConveyor.SetImage(imagesDir + ConveyorImageName);
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mSink.SetComponent(this);
}

/**
 * Draw the conveyor
 * @param graphics the context to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * Set the position of the conveyor
 * @param point
 */
void Conveyor::SetPosition(wxPoint2DDouble point)
{
    mConveyor.SetInitialPosition(point.m_x, point.m_y);
    mPosition = point;

    mShaftPosition = mPosition + ConveyorShaftOffset;
}


/**
 * Install physics into the conveyor
 * @param world the b2world
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world)
{
    mConveyor.InstallPhysics(world);
}

/**
 * Rotate the conveyor
 * @param rotation the rotation
 * @param speed speed of rotation
 */
void Conveyor::Rotate(double rotation, double speed)
{
    mConveyor.SetAngularVelocity(speed);
    mSpeed = -speed;
    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(mSpeed, 0));
        }

        contact = contact->next;
    }

}


/**
 * Set contact listener for the conveyor
 * @param contactListener the contact listener to add the goal to
 */
void Conveyor::AddContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(mConveyor.GetBody(), this);

}

/**
 * Pre solve before an object makes contact
 * @param contact the b2 contact object
 * @param oldManifold oldManifold object
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

    contact->SetTangentSpeed(mSpeed);
}

/**
 * Reset the body component
 */
void Conveyor::ResetComponent()
{
}
