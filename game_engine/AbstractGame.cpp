//
//  AbstractGame.cpp
//  GameEngineBase
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "AbstractGame.h"
#include <iostream>
using namespace std;

AbstractGame::AbstractGame() : running(true), gameTime(0.0)
{
    cout << "Abstract Game started" << endl;
    std::shared_ptr<XCube2Engine> engine = XCube2Engine::getInstance();
    //step 6
    gfx = engine->getGraphicsEngine();
    eventSystem = engine->getEventEngine();
    physics = engine->getPhysicsEngine();
}

AbstractGame::~AbstractGame()
{
    cout << "Abstract Game ended" << endl;
    //step 7
    gfx.reset();
    eventSystem.reset();
    physics.reset();
    // kill engine
    XCube2Engine::quit();
}

void AbstractGame::updatePhysics()
{
    physics->update(0.016f);
}

int AbstractGame::runMainLoop()
{
    gfx->clearScreen();
    render();
    while (running) {
        gfx->setFrameStart();
        eventSystem->pollEvents();
        if (eventSystem->isPressed(Key::ESC) || eventSystem->isPressed(Key::QUIT))
            running = false;

        handleKeyEvents();
        handleMouseEvents();

        if (!paused) {
            update();
            updatePhysics();
            gameTime += 0.016;    // 60 times a sec
        }

        gfx->clearScreen();
        render();
        gfx->showScreen();

        gfx->adjustFPSDelay(16);    // atm hardcoded to ~60 FPS
    }

    return 0;
}
void AbstractGame::handleMouseEvents() {
    if (eventSystem->isPressed(Mouse::BTN_LEFT)) onLeftMouseButton();
    if (eventSystem->isPressed(Mouse::BTN_RIGHT)) onRightMouseButton();
}
void AbstractGame::onLeftMouseButton() {}
void AbstractGame::onRightMouseButton() {}
