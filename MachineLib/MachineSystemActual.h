/**
 * @file MachineSystemActual.h
 * @author Frederick Fan
 *
 * Class for the machine system
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H

#include "IMachineSystem.h"

class Machine;

/** Class for the machine system */
class MachineSystemActual : public IMachineSystem
{
private:

    ///The machine's ID number
    int mMachineNumber = 0;

    ///The number of frames
    int mFrame = 0;

    ///The frame rate
    double mFrameRate = 30;

    ///The time elapsed
    double mTime = 0;

    ///Location of the machine
    wxPoint mLocation = wxPoint(0, 0);

    ///The flag
    int mFlag = 0;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    ///The machine in the system
    std::shared_ptr<Machine> mMachine = nullptr;

    ///The resources directory
    std::wstring mResourcesDirectory;

public:

    /// Copy constructor (disabled)
    MachineSystemActual(const MachineSystemActual &) = delete;

    /// Assignment operator
    void operator=(const MachineSystemActual &) = delete;

    MachineSystemActual(std::wstring resourcesDir);

    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    void SetLocation(wxPoint location) override {mLocation = location;}

    /**
     * Get the location of the machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override {return mLocation;}

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
      * Set the current machine animation frame
      * @param frame Frame number
      */
    void SetMachineFrame(int frame) override;

    void SetMachineNumber(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override {return mMachineNumber;}

    /**
      * Set the expected frame rate in frames per second
      * @param rate Frame rate in frames per second
      */
    void SetFrameRate(double rate) override {mFrameRate = rate;}

    /**
      * Get the current machine time.
      * @return Machine time in seconds
      */
    double GetMachineTime() override {return (double)mFrame/mFrameRate;}

    /**
    * Set the flag from the control panel
    * @param flag Flag to set
    */
    void SetFlag(int flag) override {mFlag = flag;}


    void UpdateTime(double time);
};
#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
