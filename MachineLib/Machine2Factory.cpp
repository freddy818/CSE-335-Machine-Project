/**
 * @file Machine2Factory.cpp
 * @author Frederick Fan
 *
 * Factory class for creating machine 2
 */


#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Body.h"
#include "Goal.h"
#include "Pulley.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "HamsterAndConveyorFactory.h"
#include "Basket.h"
#include "Banner.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";


/**
* Constructor
* @param resourcesDir Path to the resources directory
*/
Machine2Factory::Machine2Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}


/**
 * Create the machine
 * @return the machine that was created
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
    // The machine itself
    // In this solution the machine number is passed
    // to the working machine constructor, so it knows
    // its number.
    auto machine = std::make_shared<Machine>(1);

    // Notice: All dimensions are in centimeters and assumes
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->GetPolygon()->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->GetPolygon()->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);



    auto banner = std::make_shared<Banner>(mImagesDir + L"/banner.png", mImagesDir + L"/banner-roll.png");
    banner->SetPosition(wxPoint2DDouble(100, 350));
    machine->AddComponent(banner);

    auto wedge1 = std::make_shared<Body>();
    wedge1->GetPolygon()->AddPoint(-25, 0);
    wedge1->GetPolygon()->AddPoint(25, 0);
    wedge1->GetPolygon()->AddPoint(25, 4.5);
    wedge1->GetPolygon()->AddPoint(-25, 25);
    wedge1->GetPolygon()->SetImage(mImagesDir + L"/wedge.png");
    wedge1->GetPolygon()->SetInitialPosition(-90, 320);
    machine->AddComponent(wedge1);


    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->GetPolygon()->Circle(12);
    basketball1->GetPolygon()->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->GetPolygon()->SetInitialPosition(145, 100);
    basketball1->GetPolygon()->SetDynamic();
    basketball1->GetPolygon()->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->GetPolygon()->Circle(12);
    basketball2->GetPolygon()->SetImage(mImagesDir + L"/basketball1.png");
    basketball2->GetPolygon()->SetInitialPosition(-250, 200);
    basketball2->GetPolygon()->SetDynamic();
    basketball2->GetPolygon()->SetPhysics(1, 0.5, 0.7);
    machine->AddComponent(basketball2);

    // Basketball 3
    auto basketball3 = std::make_shared<Body>();
    basketball3->GetPolygon()->Circle(12);
    basketball3->GetPolygon()->SetImage(mImagesDir + L"/basketball2.png");
    basketball3->GetPolygon()->SetInitialPosition(-90, 360);
    basketball3->GetPolygon()->SetDynamic();
    basketball3->GetPolygon()->SetPhysics(1, 0.5, 0.72);
    machine->AddComponent(basketball3);



    auto basket = std::make_shared<Basket>(mImagesDir);
    basket->SetPosition(wxPoint(145, 0));
    machine->AddComponent(basket);

    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(wxPoint2DDouble(270,0));
    machine->AddComponent(goal);


    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(wxPoint(-250,0));
    machine->AddComponent(hamster);
    hamster->SetInitiallyRunning(true);
    auto hamsterShaft = hamster->GetShaftPosition();

    auto basket2 = std::make_shared<Basket>(mImagesDir);
    basket2->SetPosition(wxPoint(-250, 50));
    machine->AddComponent(basket2);

    auto basket3 = std::make_shared<Basket>(mImagesDir);
    basket3->SetPosition(wxPoint(270, 0));
    basket3->SetBasketShot(wxPoint2DDouble(-1, 8));
    machine->AddComponent(basket3);


    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->GetPolygon()->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft);
    machine->AddComponent(pulley1);
//
    hamster->GetSource()->AddSink(pulley1->GetSink());

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    conveyor->SetPosition(wxPoint2DDouble(-100, 200));
    machine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();

    auto pulley2 = std::make_shared<Pulley>(10);
    pulley2->GetPolygon()->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft);
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);
    pulley2->GetSource()->AddSink(conveyor->GetSink());

    auto conveyor2 = std::make_shared<Conveyor>(mImagesDir);
    conveyor2->SetPosition(wxPoint2DDouble(0, 300));
    machine->AddComponent(conveyor2);
    auto conveyor2Shaft = conveyor2->GetShaftPosition();

    auto pulley3 = std::make_shared<Pulley>(10);
    pulley3->GetPolygon()->SetImage(mImagesDir + L"/pulley3.png");
    pulley3->SetPosition(conveyor2Shaft);
    machine->AddComponent(pulley3);

    pulley2->Drive(pulley3);
    pulley3->GetSource()->AddSink(conveyor2->GetSink());

    auto hamster2 = std::make_shared<Hamster>(mImagesDir);
    hamster2->SetPosition(wxPoint(-2,0));
    hamster2->SetSpeed(-2);
    machine->AddComponent(hamster2);
    auto hamster2Shaft = hamster2->GetShaftPosition();

    auto pulley4 = std::make_shared<Pulley>(10);
    pulley4->GetPolygon()->SetImage(mImagesDir + L"/pulley3.png");
    pulley4->SetPosition(hamster2Shaft);
    machine->AddComponent(pulley4);

    hamster2->GetSource()->AddSink(pulley4->GetSink());




    return machine;
}
