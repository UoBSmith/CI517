//
//  XCube2d.h
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//


#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "GraphicsEngine.h"
#include "EventEngine.h"
#include "MyPhysicsSubsystem.h"
#include "PhysicsEngine.h"

const int _ENGINE_VERSION_MAJOR = 0;
const int _ENGINE_VERSION_MINOR = 1;

class XCube2Engine {
private:
    static std::shared_ptr<XCube2Engine> instance;

    //   std::shared_ptr<MyEngineSystem> myEngineSystemInstance;
    std::shared_ptr<GraphicsEngine> gfxInstance;
    std::shared_ptr<EventEngine> eventInstance;

    // declare/initialise MyPhysicsSubsystem with shared pointer
    std::shared_ptr< MyPhysicsSubsystem> customInstance;

    // initialise physics subsystem
    std::shared_ptr<PhysicsEngine> physicsInstance;

    XCube2Engine();
public:
    /**
    * @return the instance of game engine
    * @exception throws EngineException if init of any submodules failed
    */
    static std::shared_ptr<XCube2Engine> getInstance();
    ~XCube2Engine();

    // Step 3 - Subsystems accessed with following accessors and return appropriate subsystem of engine
    std::shared_ptr<GraphicsEngine> getGraphicsEngine() { return gfxInstance; }
    std::shared_ptr<EventEngine> getEventEngine() { return eventInstance; }

    // Get custom engine
    std::shared_ptr<MyPhysicsSubsystem> getMyPhysicsSubsystem() { return customInstance; }

    std::shared_ptr<PhysicsEngine> getPhysicsEngine() { return physicsInstance; }

    /**
    * Quits the engine, closes all the subsystems
    *
    * All subsequent calls to any of subsystems will have undefined behaviour
    */
    static void quit();


};

typedef XCube2Engine XEngine;
