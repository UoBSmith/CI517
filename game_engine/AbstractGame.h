//
//  AbstractGame.h
//  GameEngineBase
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master


#include <stdio.h>
#include "XCube2d.h"

class AbstractGame {
private:
    /* Main loop control */
    //Add handlers
    void handleMouseEvents();
    void updatePhysics();
protected:
    AbstractGame();
    virtual ~AbstractGame();

    // Get pointers
    std::shared_ptr<GraphicsEngine> gfx;
    std::shared_ptr<EventEngine> eventSystem;
    // Get pointer to my custom physics system into game demo
    std::shared_ptr<MyPhysicsSubsystem> customSystem;
    // Get pointer to PhysicsEngine
    std::shared_ptr<PhysicsEngine> physics;

    /* Main loop control */
    bool running;
    bool paused;
    double gameTime;
    virtual void update() = 0;
    virtual void render() = 0;

    //Define input handlers
    virtual void handleKeyEvents() = 0;
    virtual void onLeftMouseButton();
    virtual void onRightMouseButton();


    //Define game controls
    void pause() { paused = true; }
    void resume() { paused = false; }

public:
    int runMainLoop();

};
