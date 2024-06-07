#pragma once

#include <stdio.h>

class MyPhysicsSubsystem
{
    friend class XCube2Engine; //make sure
private:
    MyPhysicsSubsystem();
public:
    ~MyPhysicsSubsystem();
    void otherfunction();
};

