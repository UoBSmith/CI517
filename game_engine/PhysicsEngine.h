#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include <vector>
#include <memory>
#include "GameMath.h"

// Default gravity value
static const float DEFAULT_GRAVITY = -1.0f;

class PhysicsObject;

// My Rigidbody Subsystem ----------------------------------------------------------------------------------------
class RigidBody {
public:
    Point2 position; // Pos of rigid body
    Vector2f velocity; // Vel of the rigid body
    float mass; // Mass of the rigid body
    float friction; // Friction value variable
    float drag; // Drag val var
    float bounciness; // Bounciness var

    // Constructor to initialise Rigidbody
    RigidBody(const Point2& pos, float m, float f, float d, float b)
        : position(pos), mass(m), friction(f), drag(d), bounciness(b), velocity(0, 0) {}

    // Apply force to rigidbody
    void applyForce(const Vector2f& force) {
        Vector2f acceleration(force.x / mass, force.y / mass); // Calculate acceleration
        velocity.x += acceleration.x; // Update x vel
        velocity.y += acceleration.y; // Update y vel
    }

    // Update the pos of the rigidbody based on vel and drag
    void update(float deltaTime) {
        velocity.x *= (1 - drag); // drag to X
        velocity.y *= (1 - drag); // drag to Y
        position.x += velocity.x * deltaTime; //update x pos
        position.y += velocity.y * deltaTime; //update y pos
    }
};
// ---------------------------------------------------------------------------------------------------------------

class PhysicsEngine
{
    friend class XCube2Engine;
    friend class PhysicsObject;

private:
    Vector2f gravity; // gravity vector
    std::vector<std::shared_ptr<RigidBody>> rigidBodies; // List rigidbodies

    PhysicsEngine();
    //std::vector<std::shared_ptr<PhysicsObject>> objects;

public:
    /**
    * Note that gravity is naturally a negative value
    * update interval in seconds
    */
    Point2 center;
    float lX, lY, hlX, hlY;

    void setGravity(float gravityValue, float worldUpdateInterval); // set gravity val and update
    void update(float deltaTime); // update rigidbodies
    void registerRigidBody(std::shared_ptr<RigidBody> body); // register new rigidbody
    void applyGravity(std::shared_ptr<RigidBody>  body); // apply gravity to rigidboyd

    Point2 getCenter() { return center; }
    float getLengthX() { return lX; }
    float getLengthY() { return lY; }
    float getHalfLengthX() { return hlX; }
    float getHalfLengthY() { return hlY; }
    //bool isColliding(const RigidBody& other);

};

class PhysicsObject
{
    friend class GraphicsEngine;

protected:
    Point2 center;
    float lX, lY, hlX, hlY;    // lengths and half lengths
    Vector2f force;

    void applyForce(const Vector2f&);
public:
    PhysicsObject(const Point2& center, float x, float y);

    Point2 getCenter() { return center; }
    float getLengthX() { return lX; }
    float getLengthY() { return lY; }
    float getHalfLengthX() { return hlX; }
    float getHalfLengthY() { return hlY; }

    bool isColliding(const PhysicsObject& other); 
    /**
    * If we have different implementations of engines/gravity
    * this can be very useful
    */
    void applyForceVertical(const float& speed);
    void applyForceHorizntal(const float& speed);
    virtual void applyGravity(const std::shared_ptr<PhysicsEngine>& engine);

    virtual void applyAntiGravity(const PhysicsEngine& engine);

};

#endif /* PhysicsEngine_hpp */

