/**
 * @file Basket.cpp
 * @author Frederick Fan
 */

#include "pch.h"
#include "Basket.h"

/// The size of the basket in centimeters
const double BasketSize = 40;

/// Delay between when the ball hits the basket
/// and when it is shot out
const double BasketDelay = 1.0;

/// The direction we shoot the ball out of the basket
const wxPoint2DDouble BasketShot = wxPoint2DDouble(1, 7);

/// Image to draw for the goal
const std::wstring BasketImage = L"/basket.png";


///The thickness of the side basket polygon
const int BasketSidePolygonThickness = 4;

///The thickness of the bottom basket polygon
const int BasketBottomPolygonThickness = 9;


/**
 * Draw the basket component
 * @param graphics the context being drawn on
 */
void Basket::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBasket.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, 0);
//    mBasketBottom.Draw(graphics);
//    mBasketLeft.Draw(graphics);
//    mBasketRight.Draw(graphics);
}

/**
 * Update the time of the component
 * @param time time to add
 */
void Basket::UpdateTime(double time)
{
    Component::UpdateTime(time);
    if (mInBasket)
    {
        mTimeInBasket += time;
    }

}

/**
 * Set the position of the basket
 * @param point the position to set to
 */
void Basket::SetPosition(wxPoint2DDouble point)
{
    mPosition = point;
    mBasketBottom.SetInitialPosition(point.m_x, point.m_y);
    mBasketLeft.SetInitialPosition(point.m_x-BasketSize/2, point.m_y);
    mBasketRight.SetInitialPosition(point.m_x+BasketSize/2, point.m_y);
}


/**
 * Install physics into the baskets polygon components
 * @param world the b2World object of the machine
 */
void Basket::InstallPhysics(std::shared_ptr<b2World> world)
{
    mBasketBottom.InstallPhysics(world);
    mBasketRight.InstallPhysics(world);
    mBasketLeft.InstallPhysics(world);


}

/**
 * Add the basket to the world's contact listener
 * @param contactListener the contact listener to add to
 */
void Basket::AddContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(mBasketBottom.GetBody(), this);

}

/**
 * reset the basket component
 */
void Basket::ResetComponent()
{
    mTimeInBasket = 0;
    mInBasket = false;
}


/**
 * Constructor
 * @param imagesDir the image directory
 */
Basket::Basket(std::wstring imagesDir)
{
    mBasket.SetImage(imagesDir + BasketImage);
    mBasket.BottomCenteredRectangle(BasketSize);

    mBasketBottom.BottomCenteredRectangle(wxSize(BasketSize, BasketBottomPolygonThickness));
    mBasketBottom.SetColor(*wxBLUE);


    mBasketLeft.BottomCenteredRectangle(BasketSidePolygonThickness,BasketSize);
    mBasketLeft.SetColor(*wxBLUE);

    mBasketRight.BottomCenteredRectangle(BasketSidePolygonThickness,BasketSize);
    mBasketRight.SetColor(*wxBLUE);

    mBasketShot = BasketShot;

}

/**
 * handle the presolve, aka prior to the contact
 * @param contact the contact
 * @param oldManifold old manifold
 */
void Basket::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    //mark that the ball has hit the basket
    mInBasket = true;

    //mTimeInBasket will be incremented in update whenever mInBasket is true
    if (mTimeInBasket >= BasketDelay)
    {
        //Once we are in the basket longer than the delay, we reset the values and set the linear velocity of the
        //object in the basket
        mTimeInBasket = 0;
        mInBasket = false;
        contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(mBasketShot.m_x, mBasketShot.m_y));
        //FixtureB is the object that is in the basket
    }

}
