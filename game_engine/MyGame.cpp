//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//

#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), numKeys(14), box{ 20, 20, 20, 20 }, box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), showThrusterUp(false), showThrusterDown(false), showThrusterLeft(false), showThrusterRight(false), phy({ 0,0 }, 10, 100), phyobj2({ 0,400 }, 2000, 10)
{
    gfx->setVerticalSync(true); // turns v sync on
    init();
    loadResources();

    // call it in the myGame
    //customSystem->otherfunction();

    physics->setGravity(2, 2); // set gravity in engine

    // initialize rigidbodies with pos, mass, friction, drag, and bounciness
    boxRigidBody = std::make_shared<RigidBody>(Point2(20, 10), 1.0f, 0.1f, 0.01f, 10.5f);
    box2RigidBody = std::make_shared<RigidBody>(Point2(0, 100), 1.0f, 0.1f, 0.01f, 10.5f);

    // register the rigidbodies with the phys engine
    physics->registerRigidBody(boxRigidBody);
    physics->registerRigidBody(box2RigidBody);

    // initialize game keys at random positions
    //for (int i = 0; i < numKeys; i++)

    // Access custom defined functions w/shared pointers --------------------------------------------------------

    //gfx->MyCustomFunction();

    // ----------------------------------------------------------------------------------------------------------

    // Draw points on random location
    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}
MyGame::~MyGame()
{
    Mix_FreeChunk(collectSound); // free the sound effect
    Mix_CloseAudio(); // close the audio device
}

void MyGame::init() {
    // Initialize SDL_mixer
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void MyGame::loadResources() {
    // Load the sound effect
    collectSound = Mix_LoadWAV("assets/tap.wav");
}

void MyGame::handleKeyEvents()
{
    int speed = 15;
    static bool wKeyPressed = false;
    static bool sKeyPressed = false;
    static bool aKeyPressed = false;
    static bool dKeyPressed = false; // static bools used to retain its value between frames

    if (eventSystem->isPressed(Key::W))
    {
        boxRigidBody->applyForce(Vector2f(0, -speed)); // move up
        showThrusterDown = true; // make thruster fire appear
        if (!wKeyPressed) {
            printf("\nW key pressed. Player thrusting up.");
            wKeyPressed = true;
        }
    }
    else {
        wKeyPressed = false;
        showThrusterDown = false; // hide thruster
    }

    if (eventSystem->isPressed(Key::S))
    {
        boxRigidBody->applyForce(Vector2f(0, speed)); // move down
        showThrusterUp = true; //make thruster fire appear
        if (!sKeyPressed) {
            printf("\nS key pressed. Player thrusting down.");
            sKeyPressed = true;
        }
    }
    else {
        sKeyPressed = false;
        showThrusterUp = false; //hide thruster
    }

    if (eventSystem->isPressed(Key::A))
    {
        boxRigidBody->applyForce(Vector2f(-(speed / 3), 0)); // move left
        showThrusterRight = true; // make thruster appear
        if (!aKeyPressed) {
            printf("\nA key pressed. Player thrusting left.");
            aKeyPressed = true;
        }
    }
    else {
        aKeyPressed = false;
        showThrusterRight = false; //hide thruster
    }

    if (eventSystem->isPressed(Key::D))
    {
        boxRigidBody->applyForce(Vector2f((speed / 3), 0)); // move right
        showThrusterLeft = true; // thruster appear
        if (!dKeyPressed) {
            printf("\nD key pressed. Player thrusting right.");
            dKeyPressed = true;
        }
    }
    else {
        dKeyPressed = false;
        showThrusterLeft = false; // hide thruster
    }
}


void MyGame::update() {

    float deltaTime = 0.016f; // based on 60 FPS. each frame is ~0.016 secs

    physics->update(deltaTime);  // Update the physics engine

    // Update the positions of the SDL rectangles based on the rigid body positions
    box.y = static_cast<int>(boxRigidBody->position.y);
    box.x = static_cast<int>(boxRigidBody->position.x);
    //box2.x = static_cast<int>(box2RigidBody->position.x);
    //box2.y = static_cast<int>(box2RigidBody->position.y);

    //if (!phy.isColliding(phyobj2))
    //{
    //    phy.applyGravity(physics);
    //}
    for (auto key : gameKeys)
    {
        SDL_Rect keyRect = { key->pos.x, key->pos.y, 10, 10 };
        if (key->isAlive && SDL_HasIntersection(&box, &keyRect)) {
            score += 400;
            key->isAlive = false; 
            numKeys--;
            std::cout << "\nScore: " << score;
            std::cout << "\nKeys remaining: " << numKeys;
            Mix_PlayChannel(-1, collectSound, 0); // play collect sound
        }
    }
    if (numKeys == 0 && !gameWon)
    {
        gameWon = true;
        std::cout << "\nYou Won! Your score was: " << score << "\nPress Esc to exit.";
    }
}


void MyGame::render()
{
    gfx->setDrawColor(SDL_COLOR_BLUE);
    gfx->drawRect(box);
    gfx->fillRect(box.x, box.y, box.h, box.w);

    gfx->setDrawColor(SDL_COLOR_YELLOW);
    for (auto key : gameKeys)
        if (key->isAlive)
        {
            //gfx->drawCircle(key->pos, 5); // draw collectibles
            gfx->drawStar(key->pos.x, key->pos.y, 15, 15);
        }

    // thrusters
    SDL_Rect thrusterRect;
    gfx->setDrawColor(SDL_COLOR_ORANGE); // set to orange for thrusters (fire)

    if (showThrusterUp) {
        thrusterRect = { box.x, box.y - 5, box.w, 5 }; //above
        gfx->fillRect(&thrusterRect);
    }
    if (showThrusterDown) {
        thrusterRect = { box.x, box.y + box.h, box.w, 5 }; // below
        gfx->fillRect(&thrusterRect);
    }
    if (showThrusterLeft) {
        thrusterRect = { box.x - 5, box.y, 5, box.h }; // left
        gfx->fillRect(&thrusterRect);
    }
    if (showThrusterRight) {
        thrusterRect = { box.x + box.w, box.y, 5, box.h }; // right
        gfx->fillRect(&thrusterRect);
    }

    renderUI();
}
void MyGame::renderUI() {
    gfx->setDrawColor(SDL_COLOR_AQUA);
    std::string scoreStr = "Score: " + std::to_string(score);

    SDL_Color textColor = {SDL_COLOR_WHITE};
    gfx->drawText(scoreStr, 10, 10, textColor);

    if (gameWon)
    {
        gfx->drawText("You Won!", 320, 280, textColor);
    }
}

