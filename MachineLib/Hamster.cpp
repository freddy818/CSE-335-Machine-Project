/**
 * @file Hamster.cpp
 * @author Frederick Fan
 *
 * class for hamsters
 */

#include "pch.h"
#include "Hamster.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"
#include "ContactListener.h"


/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};

///for items that have no rotation
const double NoRotation = 0;

///How long a full rotation is in seconds
const double FullRotationLength = 0.25;

///A default speed that the hamster can be set to in case the speed for the hamster was not set in the factory and it
/// was asleep initially
const double DefaultSpeed = 1;


/**
 * Constructor
 * @param imagesDir the image directory
 */
Hamster::Hamster(std::wstring imagesDir)
{
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mCage.SetImage(imagesDir + HamsterCageImage);


    for (auto hamsterImage : HamsterImages)
    {
        auto hamster = std::make_shared<cse335::Polygon>();
        hamster->SetImage(imagesDir + hamsterImage);
        hamster->BottomCenteredRectangle(HamsterSize);
        mHamsters.push_back(hamster);

    }

    mWheel.SetImage(imagesDir + HamsterWheelImage);
    mWheel.CenteredSquare(HamsterWheelSize);
    mSource.SetComponent(this);

    mSpeed = DefaultSpeed; //Setting the mSpeed to a default speed in constructor in case a speed was not set
                            //manually
}

/**
 * Update the time
 * @param time the time to add
 */
void Hamster::UpdateTime(double time)
{
    Component::UpdateTime(time);

    if (!mIsAsleep)
    {
        mRotation += -mSpeed * time;
    }
    else
    {
        mRotation = 0;
    }
    mSource.Rotate(mRotation, -mSpeed);

}

/**
 * Draw the hamster
 * @param graphics the context being drawn on
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    mCage.Draw(graphics);
    mWheel.DrawPolygon(graphics, mPosition.m_x+WheelCenter.m_x, mPosition.m_y+WheelCenter.m_y, mRotation);
    int hamsterIndex = 0;

    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y + WheelCenter.m_y);

    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }

    if (mIsAsleep)
    {
    }
    else
    {
        //I am saying that a rotation cycle is .25s and a rotation of hamster images is 4 images, so I should
        //check every fourth of a rotation cycle to change the image. Change the image by just changing the index
        //multiplying FullRotationLength/HamsterSpeed by 2 and 3 in order to increment it by 1/4
        if(abs(mRotation) <= FullRotationLength/HamsterSpeed)
        {
            hamsterIndex = 1;
        }
        else if (abs(mRotation) <= FullRotationLength/HamsterSpeed*2  )
        {
            hamsterIndex = 2;
        }
        else if (abs(mRotation) <= FullRotationLength/HamsterSpeed*3 )
        {
            hamsterIndex = 3;
        }
        else if (abs(mRotation) <= FullRotationLength)
        {
           hamsterIndex = 2;
        }
        else
        {
            hamsterIndex = 1;
            mRotation -= mRotation;
        }

    }

    mHamsters[hamsterIndex]->DrawPolygon(graphics, 0, -WheelCenter.m_y, NoRotation);
    graphics->PopState();


}

/**
 * Set the position of the hamster
 * @param point the position to set to
 */
void Hamster::SetPosition(wxPoint2DDouble point)
{
    mPosition = point;
    mCage.SetInitialPosition(point.m_x, point.m_y);

    mHamsterShaft.m_x = point.m_x + HamsterShaftOffset.m_x;
    mHamsterShaft.m_y = point.m_y + HamsterShaftOffset.m_y;

}


/**
 * Install physics on the hamster cage
 * @param world the b2world
 */
void Hamster::InstallPhysics(std::shared_ptr<b2World> world)
{
    mCage.InstallPhysics(world);
}

/**
 * Add the hamster to the worlds contact listener
 * @param contactListener the contact listener
 */
void Hamster::AddContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(mCage.GetBody(), this);
}

/**
 * Set the hamster to run initially
 * @param run the bool
 */
void Hamster::SetInitiallyRunning(bool run)
{
    mInitiallyRunning = run;
    mIsAsleep = !run;
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    // Turn the hamster on
    mIsAsleep = false;
}

/**
 * Reset the hamster component
 */
void Hamster::ResetComponent()
{
    if (!mInitiallyRunning)
    {
        mIsAsleep = true;
    }
}
