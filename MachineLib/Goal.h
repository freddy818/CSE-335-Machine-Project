/**
 * @file Goal.h
 * @author Frederick Fan
 *
 * the class for the goal component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include "Component.h"

class ContactListener;


/** the class for the goal component */
class Goal : public Component, public b2ContactListener
{
private:

    /// The polygon object for the goal image
    cse335::Polygon mGoalPolygon;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;

    ///the score on the scoreboard
    int mScore = 0;

    ///position of the component
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);


public:

    /// Destructor
    virtual ~Goal() {}

    /** Copy constructor disabled */
    Goal(const Goal &) = delete;

    /** Assignment operator disabled */
    void operator=(const Goal &) = delete;

    Goal(std::wstring directory);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint position);
    void UpdateTime(double time) override;
    void SetPosition(wxPoint2DDouble point);

    void InstallPhysics(std::shared_ptr<b2World> world) override;
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    void AddContactListener(std::shared_ptr<ContactListener> contactListener) override;

    void ResetComponent() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
