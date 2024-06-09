/**
 * @file Basket.h
 * @author Frederick Fan
 *
 * Class for the basket component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKET_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKET_H

#include "Component.h"

/** Class for the basket component of the machine */
class Basket : public Component, public b2ContactListener
{
private:

    ///The polygon object for the basket
    cse335::Polygon mBasket;

    /// The polygon object for the bottom of the basket
    cse335::PhysicsPolygon mBasketBottom;

    /// Physics polygon for the Right side of the basket
    cse335::PhysicsPolygon mBasketRight;

    /// Polygon for the left side of the basket
    cse335::PhysicsPolygon mBasketLeft;

    ///position of the component
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);

    ///The amount of time the ball has been in the basket
    double mTimeInBasket = 0;

    ///bool representing if the ball is in the basket
    bool mInBasket = false;

    ///The direction at which we shoot the basketball at
    wxPoint2DDouble mBasketShot = wxPoint2DDouble(0, 0);


public:

    /// Destructor
    virtual ~Basket() {}

    /** Copy constructor disabled */
    Basket(const Basket &) = delete;

    /** Assignment operator disabled */
    void operator=(const Basket &) = delete;

    Basket(std::wstring directory);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void UpdateTime(double time) override;
    void SetPosition(wxPoint2DDouble point);

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    void AddContactListener(std::shared_ptr<ContactListener> contactListener) override;

    void ResetComponent() override;

    /**
     * Set the basket shot
     * @param basketShot basket shot to set to
     */
    void SetBasketShot(wxPoint2DDouble basketShot) { mBasketShot = basketShot;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKET_H
