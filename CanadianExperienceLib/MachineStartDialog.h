/**
 * @file MachineStartDialog.h
 * @author Frederick Fan
 *
 * Handle the dialog box for setting the machine animation start frames
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDIALOG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDIALOG_H

class Picture;

/**
 * Dialog box for setting the machine animation start frames
 */
class MachineStartDialog : public wxDialog
{
private:

    ///The Picture
    std::shared_ptr<Picture> mPicture = nullptr;

    ///The start animation frame for machine 1
    int mMachineOneStartFrame = 0;

    ///The start animation frame for machine 2
    int mMachineTwoStartFrame = 0;

    void OnOK(wxCommandEvent& event);


public:
    MachineStartDialog(wxWindow* parent,std::shared_ptr<Picture> picture);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDIALOG_H
