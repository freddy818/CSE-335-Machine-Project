/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    //Create and add machine one
    auto machineOne = std::make_shared<Actor>(L"Machine One");
    machineOne->SetPosition(wxPoint(900, 500));

    auto machineOneDrawable = std::make_shared<MachineDrawable>(resourcesDir,L"Machine One Drawable", 1);
    machineOne->AddDrawable(machineOneDrawable);
    machineOne->SetRoot(machineOneDrawable);
    picture->SetMachineOneDrawable(machineOneDrawable);
    picture->AddActor(machineOne);

    //Create and add machine Two
    auto machineTwo = std::make_shared<Actor>(L"Machine Two");
    machineTwo->SetPosition(wxPoint(250, 500));

    auto machineTwoDrawable = std::make_shared<MachineDrawable>(resourcesDir,L"Machine Two Drawable", 2);
    machineTwo->AddDrawable(machineTwoDrawable);
    machineTwo->SetRoot(machineTwoDrawable);
    picture->SetMachineTwoDrawable(machineTwoDrawable);
    picture->AddActor(machineTwo);


    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);




    return picture;
}

