/**
 * @file MachineDrawable.h
 * @author Frederick Fan
 *
 * Adapter class for the machine
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include "Drawable.h"
#include <machine-api.h>

class MainFrame;

/** Adapter class for the machine */
class MachineDrawable : public Drawable
{
private:


    ///The Machine system
    std::shared_ptr<IMachineSystem> mMachineSystem;

    ///The timeline for the machine
    Timeline *mTimeline = nullptr;

    ///The frame of the machine
    int mFrame = 0;

    ///The frame at which we want the machine to start moving
    int mStartFrame = 0;

public:


    /// Default constructor (disabled)
    MachineDrawable() = delete;

    /// Copy constructor (disabled)
    MachineDrawable(const MachineDrawable &) = delete;

    /// Assignment operator
    void operator=(const MachineDrawable &) = delete;

    MachineDrawable(const std::wstring &filename, const std::wstring& name, const int machineId);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    void ShowMachineDialog(wxWindow * parent);


    void SetTimeline(Timeline * timeline) override;

    /**
     * Set the start frame of animation for the machine
     * @param frame the frame to set to
     */
    void SetStartFrame(int frame) {mStartFrame = frame;}

    /**
     * Get the machine Id
     * @return the machine's id
     */
    int GetMachineId() {return mMachineSystem->GetMachineNumber();}

    /**
     * Set the machine ID
     * @param id the id to set to
     */
    void SetMachineID(const int id) {mMachineSystem->SetMachineNumber(id);}

    /**
     * Getter for the machine's animation start frame
     * @return the machine animation start frame
     */
    int GetMachineStartFrame() const { return mStartFrame;}


};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
