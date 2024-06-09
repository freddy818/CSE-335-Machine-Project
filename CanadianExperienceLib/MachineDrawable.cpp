/**
 * @file MachineDrawable.cpp
 * @author Frederick Fan
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * Constructor
 * @param filename the filename for the images
 * @param name the machine's name
 * @param machineId the machine's id
 */
MachineDrawable::MachineDrawable(const std::wstring &filename, const std::wstring& name, const int machineId) : Drawable(name)
{

    MachineSystemFactory factory(filename);
    std::shared_ptr<IMachineSystem> machine = factory.CreateMachineSystem();
    mMachineSystem = machine;
    mMachineSystem->SetMachineNumber(machineId);
}

/**
 * Draw the machine
 * @param graphics context that is being drawn on
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mTimeline->GetCurrentFrame() >= mStartFrame)
    {
        mFrame = mTimeline->GetCurrentFrame()-mStartFrame;
    }
    else
    {
        mFrame = 0;
    }
    mMachineSystem->SetMachineFrame(mFrame);

    double scale = 0.5f;
    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);
    mMachineSystem->SetLocation(wxPoint(0,0));

    mMachineSystem->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Test of the machine drawable is clicked
 * @param pos position that is clicked
 * @return bool if it is clicked
 */
bool MachineDrawable::HitTest(wxPoint pos)
{

    return false;
}

/**
 * Show the machine dialog box
 * @param parent the parent frame
 */
void MachineDrawable::ShowMachineDialog(wxWindow *parent)
{
    MachineDialog dlg(parent, mMachineSystem);
    if (dlg.ShowModal() == wxID_OK)
    {

    }
}

/**
 * Set the timeline for the machine
 * @param timeline timeline to set to
 */
void MachineDrawable::SetTimeline(Timeline *timeline)
{
    Drawable::SetTimeline(timeline);
    mTimeline = timeline;
}





