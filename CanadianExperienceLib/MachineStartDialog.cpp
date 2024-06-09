/**
 * @file MachineStartDialog.cpp
 * @author Frederick Fan
 */


#include "pch.h"
#include "MachineStartDialog.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include "Picture.h"
#include "MachineDrawable.h"


/**
 * Constructor
 * @param parent the parent frame
 * @param picture the picture the machines are a part of
 */
MachineStartDialog::MachineStartDialog(wxWindow *parent, std::shared_ptr<Picture> picture) : mPicture(picture)
{

    wxXmlResource::Get()->LoadDialog(this, parent, L"MachineStartDlg");

    mMachineOneStartFrame = mPicture->GetMachineOneDrawable()->GetMachineStartFrame();
    mMachineTwoStartFrame = mPicture->GetMachineTwoDrawable()->GetMachineStartFrame();

    Bind(wxEVT_BUTTON, &MachineStartDialog::OnOK, this, wxID_OK);

    auto machineOneCtrl = XRCCTRL(*this, "MachineOneStartFrame", wxTextCtrl);
    wxIntegerValidator<int> machineOneFrameValidator(&mMachineOneStartFrame);
    machineOneFrameValidator.SetRange(0, mPicture->GetTimeline()->GetNumFrames());
    machineOneCtrl->SetValidator(machineOneFrameValidator);

    auto machineTwoCtrl = XRCCTRL(*this, "MachineTwoStartFrame", wxTextCtrl);
    wxIntegerValidator<int> machineTwoFrameValidator(&mMachineTwoStartFrame);
    machineTwoFrameValidator.SetRange(0, mPicture->GetTimeline()->GetNumFrames());
    machineTwoCtrl->SetValidator(machineTwoFrameValidator);


}


/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineStartDialog::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        // make sure they are not null before setting them so program will not crash if the picture is missing a machine
        if (mPicture->GetMachineOneDrawable() != nullptr)
        {
            mPicture->GetMachineOneDrawable()->SetStartFrame(mMachineOneStartFrame);
        }
        if (mPicture->GetMachineTwoDrawable() != nullptr)
        {
            mPicture->GetMachineTwoDrawable()->SetStartFrame(mMachineTwoStartFrame);
        }

        EndModal(wxID_OK);
    }
}
