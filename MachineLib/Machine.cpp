/**
 * @file Machine.cpp
 * @author Frederick Fan
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "ContactListener.h"
#include "MachineSystemActual.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;


/**
 * constructor
 * @param machineId the id of the machine
 */
Machine::Machine(int machineId)
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
    mMachineId = machineId;
}

/**
 * Draw the machine
 * @param graphics the graphics context to draw on
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto component : mComponents)
    {

        component->Draw(graphics);
    }

}

/**
 * Add a component to the collection
 * @param component the component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetParentMachine(this);
}

/**
 * Update the machine in time
 * @param elapsed Elapsed time in seconds
 */
void Machine::Update(double elapsed)
{
    // Call Update on all of our components so they can advance in time

    for (auto component : mComponents)
    {
        component->UpdateTime(elapsed);
    }
    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Reset the b2World
 */
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    InstallPhysics();

    for (auto component : mComponents)
    {
        component->ResetComponent();
    }


}

/**
 * Install physics and a contact filter to all the componenets that need it
 */
void Machine::InstallPhysics()
{
    for (auto component : mComponents)
    {
        component->InstallPhysics(mWorld);
        component->AddContactListener(mContactListener);
    }
}









