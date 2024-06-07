
#include "PhysicsEngine.h"
//#include "MyGame.cpp"

// constructor for PhysicsObject
PhysicsObject::PhysicsObject(const Point2& center, float x, float y) : center(center), lX(x), lY(y), hlX(x / 2.0f), hlY(y / 2.0f), force(0.0f, 0.0f)
{



}

bool PhysicsObject::isColliding(const PhysicsObject& other)
{
    Rectf r1 = { center.x - hlX, center.y - hlY, lX, lY };
    Rectf r2 = { other.center.x - other.hlX, other.center.y - other.hlY, other.lX, other.lY };

    return r1.intersects(r2);
}

void PhysicsObject::applyForce(const Vector2f& v) {
    force = v;
}

void PhysicsObject::applyGravity(const std::shared_ptr<PhysicsEngine>& engine)
{
    center += engine->gravity;
}
void PhysicsObject::applyForceVertical(const float& speed)
{
    center.y -= speed;
}
void PhysicsObject::applyForceHorizntal(const float& speed)
{
    center.x -= speed;
}
void PhysicsObject::applyAntiGravity(const PhysicsEngine& engine)
{
    center -= engine.gravity;
}



/* PHYSICS ENGINE */

PhysicsEngine::PhysicsEngine() : gravity(Vector2f(0, DEFAULT_GRAVITY))
{

}

//bool PhysicsEngine::isColliding(const RigidBody& other)
//{
//    Rectf r1 = { center.x - hlX, center.y - hlY, lX, lY };
//    Rectf r2 = { other.center.x - other.hlX, other.center.y - other.hlY, other.lX, other.lY };
//
//    return r1.intersects(r2);
//}

void PhysicsEngine::setGravity(float val, float interval)
{

    gravity = Vector2f(0, val * interval);

}

void PhysicsEngine::registerRigidBody(std::shared_ptr<RigidBody> body)
{
    rigidBodies.push_back(body);
}

// apply gravity to rigid body
void PhysicsEngine::applyGravity(std::shared_ptr<RigidBody> body) {
    Vector2f force = Vector2f(gravity.x * body->mass, gravity.y * body->mass);
    body->applyForce(force);
}

void PhysicsEngine::update(float deltaTime)
{
    for (auto& body : rigidBodies) {
        applyGravity(body);  // apply gravity to each body
        body->update(deltaTime);  // Update bodys pos and vel

        int boxSize = 0;

        // collision with floor
        if (body->position.y > 580 - boxSize) { 
            body->position.y = 580 - boxSize;
            body->velocity.y = 0;
            printf("\nPlayer collided with roof\nAronSmith-CI517-2023-24");
        }
        // collision with top
        if (body->position.y < 0) { 
            body->position.y = 0;
            body->velocity.y = 0;
            printf("\nPlayer collided with roof");
        }
        //Collision with left
        if (body->position.x < 0) { 
            body->position.x = 0;
            body->velocity.x = 0;
            printf("\nPlayer collided with left wall");
        }
        //collision with right
        if (body->position.x > 780 - boxSize) {  
            body->position.x = 780 - boxSize;
            body->velocity.x = 0;
            printf("\nPlayer collided with right wall");
        }
    }
}
