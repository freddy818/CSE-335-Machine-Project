/**
 * @file Goal.cpp
 * @author Frederick Fan
 *
 * the class for the goal component
 */

#include "pch.h"

#include <string>
#include "Goal.h"
#include "ContactListener.h"
#include "Machine.h"


/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);

///The font color
const wxColour FontColor = wxColor(255,255,255);

///const to represent 10
const int Ten = 10;

/**
 * Test if something made the goal
 * @param position the position that was hit
 * @return a bool representing if something went in the goal
 */
bool Goal::HitTest(wxPoint position)
{
    return false;
}

/**
 * Draw the goal
 * @param graphics graphics context being drawn on
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mGoalPolygon.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y,0);
//    mGoal.Draw(graphics);
//    mPost.Draw(graphics);


    //code to draw the scoreboard
    wxBrush background(ScoreboardBackgroundColor);
    graphics->SetBrush(background);
    graphics->DrawRectangle(ScoreboardRectangle.m_x + mPosition.m_x,ScoreboardRectangle.m_y,
                            ScoreboardRectangle.m_width ,ScoreboardRectangle.m_height);

    wxString score = wxString::Format(wxT("%i%i"), mScore/Ten%Ten, mScore%Ten);

    graphics->PushState();
    graphics->Translate(mPosition.m_x + ScoreboardTextLocation.m_x,mPosition.m_y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);
    wxFont font(wxSize(ScoreboardFontSize, ScoreboardFontSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, FontColor);
    graphics->DrawText(score, 0, 0);
    graphics->PopState();

}

/**
 * Update the time
 * @param time the time to add
 */
void Goal::UpdateTime(double time)
{
    Component::UpdateTime(time);
}

/**
 * Set the position of the goal
 * @param point the position to set to
 */
void Goal::SetPosition(wxPoint2DDouble point)
{
    mPosition = point;
    mPost.SetInitialPosition(mPosition.m_x+ PostPosition.m_x,mPosition.m_y + PostPosition.m_y );
    mGoal.SetInitialPosition(mPosition.m_x+GoalPosition.m_x, mPosition.m_y + GoalPosition.m_y);
}



/**
 * Constructor
 * @param imagesDir image directory
 */
Goal::Goal(std::wstring imagesDir)
{
    mGoalPolygon.BottomCenteredRectangle(GoalSize);
    mGoalPolygon.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxBLUE);

}

/**
 * Install physics into the goal
 * @param world the machines b2World
 */
void Goal::InstallPhysics(std::shared_ptr<b2World> world)
{
    mGoal.InstallPhysics(world);
    mPost.InstallPhysics(world);


}


/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{

    mScore += 2;

}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);

}

/**
 * Add a goal to contact listener
 * @param contactListener the machines contact listener
 */
void Goal::AddContactListener(std::shared_ptr<ContactListener> contactListener)
{
    contactListener->Add(mGoal.GetBody(), this);

}

/**
 * Reset the goal component
 */
void Goal::ResetComponent()
{
    mScore = 0;
}
