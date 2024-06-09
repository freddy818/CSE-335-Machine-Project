/**
 * @file Pulley.cpp
 * @author Frederick Fan
 *
 * Class for the pulley component
 */

#include "pch.h"
#include "Pulley.h"

///Belt Color
const wxColour BeltColor = wxColour(0,0,0);

///Belt width
const int BeltWidth = 2;


/**
 * Constructor
 * @param radius radius of the pulley
 */
Pulley::Pulley(double radius) : mRadius(radius)
{
    mSink.SetComponent(this);
    mSource.SetComponent(this);
    mPolygon.CenteredSquare(mRadius * 2);

}


/**
 * Draw the pulley
 * @param graphics the context to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mConnectedPulley != nullptr)
    {
        graphics->SetPen(wxPen(BeltColor, BeltWidth));
        wxPoint2DDouble a = (mConnectedPulley->GetPosition()-GetPosition());
        a =  a/a.GetVectorLength()*mRadius;
        wxPoint2DDouble beta = wxPoint2DDouble(-a.m_y, a.m_x);
        graphics->StrokeLine(GetPosition().m_x+beta.m_x,
                             GetPosition().m_y + beta.m_y,
                             mConnectedPulley->GetPosition().m_x +beta.m_x,
                             mConnectedPulley->GetPosition().m_y + beta.m_y);
        graphics->StrokeLine(GetPosition().m_x-beta.m_x,
                             GetPosition().m_y - beta.m_y,
                             mConnectedPulley->GetPosition().m_x -beta.m_x,
                             mConnectedPulley->GetPosition().m_y - beta.m_y);
    }
    mPolygon.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, mRotation);

}

/**
 * Set the position of the pulley
 * @param point the position to set to
 */
void Pulley::SetPosition(wxPoint2DDouble point)
{
    mPosition = point;

}


/**
 * Update the time
 * @param time time to add
 */
void Pulley::UpdateTime(double time)
{
    Component::UpdateTime(time);
    mRotation += mSpeed * time;
}

/**
 * Rotate the body
 * @param rotation the rotation
 * @param speed speed of rotation
 */
void Pulley::Rotate(double rotation, double speed)
{

    //make sure that the pulleys rotation source is actually moving to change the speed
    if (rotation != 0)
    {
        mSpeed = speed;
    }
    //Rotate each sink in the source's collection of sinks
    mSource.Rotate(mRotation, mSpeed);

}

/**
 * Use a source pulley to drive a sink pulley
 * @param pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mSource.AddSink(pulley->GetSink());
    pulley->GetSink()->SetSource(&mSource);
    SetConnectedPulley(pulley);
}

/**
 * Reset the pulley component
 */
void Pulley::ResetComponent()
{
    mRotation = 0;
    mSpeed = 0;

}
