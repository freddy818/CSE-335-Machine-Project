/**
 * @file MachineSystemActual.cpp
 * @author Frederick Fan
 *
 * Class for the machine system
 */

#include "pch.h"
#include "MachineSystemActual.h"

#include "Machine.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

///The highest machine ID that you can set the system to
const int MaxMachineId = 2;

/**
 * constructor
 * @param resourcesDir the resources directory
 */
MachineSystemActual::MachineSystemActual(std::wstring resourcesDir) : mResourcesDirectory(std::move(resourcesDir))
{
    SetMachineNumber(1);
}
/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystemActual::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    // Draw your machine assuming an origin of 0,0

    mMachine->Draw(graphics);

    graphics->PopState();


}

/**
 * update the time
 * @param time the time to set to
 */
void MachineSystemActual::UpdateTime(double time)
{
    mTime += time;
}

/**
  * Set the machine number
  * @param machine An integer number. Each number makes a different machine
  */
void MachineSystemActual::SetMachineNumber(int machine)
{
    if (machine > MaxMachineId )
    {
        mMachineNumber = 1;
    }
    else
    {
        mMachineNumber = machine;
    }
    if (mMachineNumber == 2)
    {
        Machine2Factory machine2(mResourcesDirectory);
        mMachine = machine2.Create();

    }
    else if (mMachineNumber == 1)
    {
        Machine1Factory machineOne(mResourcesDirectory);
        mMachine = machineOne.Create();

    }
    mMachine->Reset();

}

/**
  * Set the current machine animation frame
  * @param frame Frame number
  */
void MachineSystemActual::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }



    for( ; mFrame < frame;  mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }

    // May need more than these, but you'll figure that out...


}
