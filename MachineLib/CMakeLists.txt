project(MachineLib)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineStandin.cpp MachineStandin.h
        Polygon.cpp Polygon.h
        DebugDraw.cpp DebugDraw.h
        Consts.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        ContactListener.cpp
        ContactListener.h
        MachineSystemStandin.cpp
        MachineSystemStandin.h
        MachineSystemActual.cpp
        MachineSystemActual.h
        Machine.cpp
        Machine.h
        MachineCFactory.cpp
        MachineCFactory.h
        Component.cpp
        Component.h
        PhysicsPolygon.cpp
        PhysicsPolygon.h
        Body.cpp
        Body.h
        RotationSink.cpp
        RotationSink.h
        Goal.cpp
        Goal.h
        Machine1Factory.cpp
        Machine1Factory.h
        HamsterAndConveyorFactory.cpp
        HamsterAndConveyorFactory.h
        Hamster.cpp
        Hamster.h
        RotationSource.cpp
        RotationSource.h
        Pulley.cpp
        Pulley.h
        Conveyor.cpp
        Conveyor.h
        Machine2Factory.cpp
        Machine2Factory.h
        Basket.cpp
        Basket.h
        Banner.cpp
        Banner.h
)

# Removed:
# Motor.cpp Motor.h Pulley.cpp Pulley.h

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

#
# Use Box2D
#
include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories()

target_include_directories(${PROJECT_NAME} PUBLIC "${box2d_SOURCE_DIR}/include/box2d")
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} box2d)
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)