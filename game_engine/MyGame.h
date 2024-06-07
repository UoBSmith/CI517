#pragma once
//
//  MyGame.h
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//


#include <stdio.h>

#include "AbstractGame.h"
#include <SDL_mixer.h> // for audio

struct GameKey {
    Point2 pos;
    bool isAlive;
};

class MyGame : public AbstractGame {
private:
    SDL_Rect box, box2; // boxes craeted with SDL
    PhysicsObject phy, phyobj2; // for collision detection
    std::shared_ptr<RigidBody> boxRigidBody, box2RigidBody;  // rigid bodies for physics simulation
    std::vector<std::shared_ptr<GameKey>> gameKeys;

    Vector2i velocity;

    Mix_Chunk* collectSound; // for star collection sound

    void init();
    void loadResources();

    /* GAMEPLAY */
    int score;
    int numKeys;
    int lives;
    bool gameWon;
    void handleKeyEvents();
    void update();
    void render();
    void renderUI();
    
    //thruster bools
    bool showThrusterUp;
    bool showThrusterDown;
    bool showThrusterLeft;
    bool showThrusterRight;

public:
    MyGame();
    ~MyGame();
};


